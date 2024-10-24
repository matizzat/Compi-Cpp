#define First_variable           CIDENT
#define First_declarador_init    CASIGNAC | CCOR_ABR
#define First_declaracion	 CVOID | CCHAR | CINT | CFLOAT
#define First_lista_declaraciones_init CIDENT
#define First_lista_declaraciones CVOID | CCHAR | CINT | CFLOAT
#define First_lista_proposiciones CMAS | CMENOS | CIDENT | CCONS_ENT | CCONS_FLO | CCONS_CAR | CNEG | CPAR_ABR | CCONS_STR | CPYCOMA | CLLA_ABR | CWHILE | CIF | CRETURN | CIN | COUT
#define First_proposicion	CMAS | CMENOS | CIDENT | CCONS_ENT | CCONS_FLO | CCONS_CAR | CNEG | CPAR_ABR | CCONS_STR | CPYCOMA | CLLA_ABR | CWHILE | CIF | CRETURN | CIN | COUT
#define First_expresion_simple  CMAS | CMENOS | CIDENT | CCONS_ENT | CCONS_FLO | CCONS_CAR | CNEG | CPAR_ABR | CCONS_STR
#define First_factor		CIDENT | CCONS_ENT | CCONS_FLO | CCONS_CAR| CNEG | CPAR_ABR | CCONS_STR
#define First_termino		CIDENT | CCONS_ENT | CCONS_FLO |CCONS_CAR | CNEG | CPAR_ABR | CCONS_STR
#define First_proposicion_expresion         CMAS | CMENOS | CIDENT | CCONS_ENT | CCONS_FLO | CCONS_CAR | CNEG | CPAR_ABR | CCONS_STR | CPYCOMA
#define First_expresion         CMAS | CMENOS | CIDENT | CCONS_ENT | CCONS_FLO | CCONS_CAR | CNEG | CPAR_ABR | CCONS_STR
#define	First_lista_expresiones CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG | CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR
#define First_constante		CCONS_ENT | CCONS_FLO | CCONS_CAR 

#include "parser.h"

int main(int argc, char *argv[])
{
	init_parser(argc, argv);
	
	unidad_traduccion(CEOF);

	match(CEOF, 10);

	last_call=1;

	error_handler(COD_IMP_ERRORES);

	return 0;
}

/********* función test ******************/

void test(set c1, set c2, int ne){
	if(!lookahead_in(c1)){
		error_handler(ne);			
		while(!lookahead_in(c1 | c2))
			scanner();	
	}
}

/********* funciones del parser ***********/

void unidad_traduccion(set folset)
{
	bool ocurrio_main = false; 

	inic_tablas();
	pushTB();

	test(folset | CVOID | CCHAR | CINT | CFLOAT, NADA, 116); // Error 116: Simbolo inesperado en unidad de traducción. Esperaba fin de archivo o 'void', 'char', 'int' o 'float'  
	while(lookahead_in(CVOID | CCHAR | CINT | CFLOAT)){
		ocurrio_main = declaraciones(folset | CVOID | CCHAR | CINT | CFLOAT) || ocurrio_main; // <- Para la historia
		
		test(folset | CVOID | CCHAR | CINT | CFLOAT, NADA, 116); 
	}

	if(!ocurrio_main)
		error_handler(84); // Error 84: Falta declarar la funcion main() 
}


bool declaraciones(set folset)
{	
	bool es_funcion_main; 
	enum Tipo tipo; 
	char* nombre = (char*)malloc(TAM_LEXEMA * sizeof(char)); 
		
	tipo = especificador_tipo(folset | CIDENT | CPAR_ABR | CASIGNAC | CCOR_ABR | CCOMA | CPYCOMA);

	strcpy(nombre, sbol->lexema);	
	match(CIDENT, 17); // Error 17: Falta identificador

	es_funcion_main = especificador_declaracion(folset, tipo, nombre);

	free(nombre); 
	
	return es_funcion_main;
}

enum Tipo especificador_tipo(set folset)
{
	enum Tipo tipo;		

	test(CVOID | CCHAR | CINT | CFLOAT, folset, 41); // Error 41: Simbolo inesperado o falta especificador de tipo	
	switch(lookahead())
	{
		case CVOID:
			scanner();
			tipo = VOID;
			break;

		case CCHAR:
			scanner();
			tipo = CHAR; 
			break;
			
		case CINT:
			scanner();
			tipo = INT;
			break;
			
		case CFLOAT:
			scanner();
			tipo = FLOAT; 
			break;
			
		default:
			error_handler(18); // Error 18: Tipo no definido
			tipo = ERROR; 
	}
	test(folset, NADA, 42); // Error 42: Simbolo inesperado despues de especificador de tipo 

	return tipo; 
}

bool especificador_declaracion(set folset, enum Tipo tipo, char* nombre)
{
	bool es_funcion_main = false;	

	test(CPAR_ABR | CASIGNAC | CCOR_ABR | CCOMA | CPYCOMA, folset, 43);	// Error 43: Simbolo inesperado o falta simb. al comienzo de especif. de declaracion
	switch(lookahead())
	{
		case CPAR_ABR:
			definicion_funcion(folset, tipo, nombre);
			if(strcmp("main", nombre) == 0)
				es_funcion_main = true; 
			break;
		
		case CASIGNAC:
		case CCOR_ABR:
		case CCOMA:
		case CPYCOMA:
			declaracion_variable(folset, tipo, nombre);
			break;
		
		default:
			error_handler(19); // Error 19: En Especificador de Declaración
	}

	return es_funcion_main; 
}

void definicion_funcion(set folset, enum Tipo tipo, char* nombre) 
{ 
	int cant_par = 0; 
	char* tipo_str = (char*)malloc(TAM_ID * sizeof(char));  
	strcpy(tipo_str, tipo_string(tipo)); 

	strcpy(inf_id->nbre, nombre);
	inf_id->clase = CLASFUNC; 
	inf_id->ptr_tipo = en_tabla(tipo_str); 
	inf_id->desc.nivel = topeTB;
	int i = insertarTS();  

	pushTB();		

	match(CPAR_ABR, 20); // Error 20: Falta (

	if(lookahead_in(CVOID | CCHAR | CINT | CFLOAT))
		cant_par = lista_declaraciones_param(folset | CPAR_CIE | CLLA_ABR);

	match(CPAR_CIE, 21); // Error 21: Falta )

	if(i != NIL)
		ts[i].ets->desc.part_var.sub.cant_par = cant_par; 

	if(strcmp("main", nombre) == 0){ 
		if(cant_par != 0)	
			error_handler(86); // Error 86: La función main() no lleva argumento	
		if(tipo != VOID)
			error_handler(85);  // Error 85: El tipo de la función main() debe ser void
	}	

	ocurrio_retorno_g = false; 
	tipo_decl_g = tipo; 
	proposicion_compuesta(folset, false);
	
	free(tipo_str); 
}

int lista_declaraciones_param(set folset)
{
	int cant_parametros = 0; 

	declaracion_parametro(folset | CCOMA);
	cant_parametros += 1; 

	test(folset | CCOMA, CVOID | CCHAR | CINT | CFLOAT, 37);  // Error 37: Símbolo incorrecto dentro de lista decl. parámetros.
	while(lookahead_in(CCOMA | CVOID | CCHAR | CINT | CFLOAT))
	{
		match(CCOMA, 64); // Error 64: Falta ,  
		declaracion_parametro(folset | CCOMA);
		test(folset | CCOMA, CVOID | CCHAR | CINT | CFLOAT, 37);	
		cant_parametros += 1;	
	}

	return cant_parametros; 
}

void declaracion_parametro(set folset)
{
	bool es_simple = true, por_valor = true; 
	enum Tipo tipo; 
	char* tipo_str = (char*)malloc(TAM_ID*sizeof(char)); 

	tipo = especificador_tipo(folset | CAMPER | CIDENT | CCOR_ABR);

	if(lookahead_in(CAMPER)){
		scanner();
		por_valor = false; 
	}

	strcpy(inf_id->nbre, sbol->lexema); 
	match(CIDENT, 17); // Error 17: Falta identificador

	if(lookahead_in(CCOR_ABR))
	{
		scanner();
		match(CCOR_CIE, 22); // Error 22: Falta ]
		es_simple = false; 
	}
	test(folset, NADA, 45); // Error 45: Simbolo inesperado despues de declarar un parametro

	if(tipo == VOID){
		error_handler(73); // Una variable, un parametro o un arreglo no puede ser de tipo void
		tipo = ERROR;	
	}

	if(!por_valor && !es_simple){
		error_handler(92); // Error 92: No se permite <tipo> & <id_arreglo> [] en la definición de un parametro 
		tipo = ERROR;	
	}

	strcpy(tipo_str, tipo_string(tipo));	
	
	// Decision: Parametros mal declarados se dan de alta con tipo ERROR. 
	inf_id->clase = CLASPAR; 
	if(es_simple)
		inf_id->ptr_tipo = en_tabla(tipo_str); 
	else{
		inf_id->ptr_tipo = en_tabla("TIPOARREGLO");	
		inf_id->desc.part_var.param.ptero_tipo_base = en_tabla(tipo_str); 
	}
	inf_id->desc.nivel = topeTB;
	inf_id->desc.part_var.param.tipo_pje = por_valor; 
	insertarTS();
	
	// Decision: Dejamos el primer identificador declarad en TS
	free(tipo_str); 
}

void lista_declaraciones_init(set folset, enum Tipo tipo)
{
	char* nombre = (char*)malloc(TAM_ID * sizeof(char)); 

	test(CIDENT, folset | First_declarador_init | CCOMA, 46); // Error 46: Simbolo inesperado al comienzo de lista decl. init

	strcpy(nombre, sbol->lexema); 
	match(CIDENT, 17); // Error 17: Falta identificador

	declarador_init(folset | CCOMA, tipo, nombre);
	test(folset | CCOMA, CIDENT | CCOMA | First_declarador_init, 107); // Error 107: Símbolo inesperado en lista de declaraciones 
	while(lookahead_in(CCOMA | CIDENT | First_declarador_init))
	{
		match(CCOMA, 64); // Error 64: Falta ,	
		
		
		strcpy(nombre, sbol->lexema); 
		match(CIDENT, 17); // Error 17: Falta identificador

		declarador_init(folset | CCOMA, tipo, nombre);
		test(folset | CCOMA, CIDENT | CCOMA | First_declarador_init, 107); 
	}

	free(nombre); 
}

void declaracion_variable(set folset, enum Tipo tipo, char* nombre)
{
	declarador_init(folset | CCOMA | CPYCOMA, tipo, nombre);

	if(lookahead_in(CCOMA))
	{
		scanner();
		lista_declaraciones_init(folset | CPYCOMA, tipo);
	}

	match(CPYCOMA, 23); // Error 23: Falta ; 
	test(folset, NADA, 115); // Error 80: Símbolo inesperado después de declaración de variable 
}

int deme_cant_elems_arr(bool constante_declarada, bool lista_declarada, int elems_constante, int elems_lista){
	int cant_elems = 0;
 
	if(!constante_declarada && !lista_declarada)
          error_handler(74); // Error 74: La cdad. de elementos de un arreglo debe ser una cte. entera en la declaracion
    
	else if(!constante_declarada && lista_declarada){
		if(elems_lista == 0)
			error_handler(75); // La cantidad de elementos de un arreglo debe ser mayor a 0
		cant_elems = elems_lista;
	}
   
	else if(constante_declarada && !lista_declarada){
		if(elems_constante <= 0)
			error_handler(75); // La cantidad de elementos de un arreglo debe ser mayor a 0
		cant_elems = max(0, elems_constante);
	}
    
	else{
		if(elems_lista > elems_constante)
			error_handler(76); // Error 76: La cantidad de valores inicializadores debe ser igual o menor al tamaño del arreglo declarado
		else if(elems_constante == 0)
			error_handler(75); // Error 75: La cantidad de elementos de un arreglo debe ser mayor a 0
		cant_elems = max(0, elems_constante);
	}
      
	return cant_elems;	
}

void declarador_init(set folset, enum Tipo tipo, char* nombre)
{
	bool es_simple = true, 
	     constante_declarada = false, 
	     lista_declarada = false; 

	int elems_constante = -1,
	    elems_lista = -1; 

	enum Tipo tipo_const; 

	char* tipo_str = (char*)malloc(TAM_ID*sizeof(char)); 

	test(folset | CASIGNAC | CCOR_ABR, CCOR_CIE, 47); // Error 47: Simbolo inesperado al comienzo de declarador init
	switch(lookahead())
	{
		case CASIGNAC:
			scanner();
			tipo_const = constante(folset);
			if(tipo != VOID && es_menor(tipo, tipo_const))
				error_handler(101); 	// Error 101: Solo se pueden realizar coersiones a tipos mas grandes
			break;

		case CCOR_ABR:
		case CCOR_CIE:
			es_simple = false;	

			match(CCOR_ABR, 22); // Error 22: Falta ]	

			if(lookahead_in(CCONS_ENT)){
				constante_declarada = true;
				elems_constante = atoi(sbol->lexema);
				constante(folset | CCOR_CIE | CASIGNAC);
			}

			match(CCOR_CIE, 22); // Error 22: Falta ]

			if(lookahead_in(CASIGNAC))
			{
				scanner();
				match(CLLA_ABR, 24); // Error 24: Falta { 
				
				elems_lista = lista_inicializadores(folset | CLLA_CIE, tipo);
				lista_declarada = true;	
			
				match(CLLA_CIE, 25); // Error 25: Falta } 
			}
			break;
	}
	test(folset, NADA, 48); // Error 48: Simbolo inesperado despues de declarador init 

	if(tipo == VOID){
		error_handler(73); // Error 73: Una variable, un parametro o un arreglo no puede ser de tipo void
		tipo = ERROR;	
	}

	strcpy(tipo_str, tipo_string(tipo)); 
	
	inf_id->clase = CLASVAR;
	inf_id->desc.nivel = topeTB;
	strcpy(inf_id->nbre, nombre); 

	if(es_simple)
		inf_id->ptr_tipo = en_tabla(tipo_str);
	else{
		inf_id->ptr_tipo = en_tabla("TIPOARREGLO"); 
		inf_id->desc.part_var.arr.ptero_tipo_base = en_tabla(tipo_str);		
		inf_id->desc.part_var.arr.cant_elem = deme_cant_elems_arr(constante_declarada,
									  lista_declarada, 
									  elems_constante,
									  elems_lista); 
	}	
	
	insertarTS();

	free(tipo_str); 
}

int lista_inicializadores(set folset, enum Tipo tipo)
{
	int cant_constantes = 0;
	enum Tipo tipo_constante; 
	bool error_impreso = false;

	tipo_constante = constante(folset | CCOMA);
	cant_constantes += 1;
	if(!error_impreso && tipo != VOID && tipo != tipo_constante){
		error_handler(77); // Error 77: El tipo de los valores inicializadores del arreglo debe coincidir con su declaración 
		error_impreso = true; 
	}
	test(folset | CCOMA, First_constante, 108); // Error 108: Símbolo inesperado en lista de inicializadores
	while(lookahead_in(CCOMA | First_constante))
	{
		match(CCOMA, 23); // Error 23: Falta ;	
		tipo_constante = constante(folset | CCOMA);
		test(folset | CCOMA, First_constante, 108);

		cant_constantes += 1;
		if(!error_impreso && tipo != VOID && tipo != tipo_constante){
			error_handler(77); 
			error_impreso = true; 
		}
	}

	return cant_constantes;
}

void proposicion_compuesta(set folset, bool vengo_de_prop)
{
	if(vengo_de_prop)
		pushTB(); 

	test(CLLA_ABR, folset | First_lista_declaraciones | First_lista_proposiciones | CLLA_CIE, 49); // Error 49: Simbolo inesperado o falta simb. al comienzo de proposicion compuesta
	match(CLLA_ABR, 24); // Error 24: Falta { 

	if(lookahead_in(CVOID | CCHAR | CINT | CFLOAT))
		lista_declaraciones(folset | First_lista_proposiciones | CLLA_CIE);

	if(lookahead_in(CLLA_ABR | CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG |
						 CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR |
						 CIF | CWHILE | CIN | COUT | CPYCOMA | CRETURN))
		lista_proposiciones(folset | CLLA_CIE);

	if(!vengo_de_prop && !ocurrio_retorno_g && 
			(tipo_decl_g == CHAR || tipo_decl_g == INT || tipo_decl_g == FLOAT)) 
		error_handler(88); // Falta return

	match(CLLA_CIE, 25); // Error 25: Falta } 
	test(folset, NADA, 50); // Error 50: Símbolo inesperado despues de proposicion compuesta

	//popTB();
	pop_nivel(); 
}

void lista_declaraciones(set folset)
{
	declaracion(folset | First_declaracion); 
	test(folset | First_declaracion, NADA, 105); // Error 105: Símbolo inesperado en lista de declaraciones 
	while(lookahead_in(CVOID | CCHAR | CINT | CFLOAT)){
		declaracion(folset | First_declaracion);	
		test(folset | First_declaracion, NADA, 105); 
	}
}

void declaracion(set folset)
{
	enum Tipo tipo; 

	tipo = especificador_tipo(folset | First_lista_declaraciones_init | CPYCOMA);

	lista_declaraciones_init(folset | CPYCOMA, tipo);

	match(CPYCOMA, 23); // Error 23: Falta ;
	test(folset, NADA, 51); // Error 51: Simbolo inesperado despues de declaracion
}

void lista_proposiciones(set folset)
{
	proposicion(folset | First_proposicion);
	test(folset | First_proposicion, NADA, 106); // Error 106: Símbolo inesperado en lista de proposiciones 
	while(lookahead_in(First_proposicion)){
		proposicion(folset | First_proposicion);
		test(folset | First_proposicion, NADA, 106); 
	}
}

void proposicion(set folset)
{
	test(CLLA_ABR | CWHILE | CIF | CIN | COUT | First_proposicion_expresion | CRETURN, folset, 52); // Error 52: Simbolo inesperado o falta simb. al comienzo de proposicion
	switch(lookahead())
	{
		case CLLA_ABR:
			proposicion_compuesta(folset, true);
			break;
		
		case CWHILE:
			proposicion_iteracion(folset);
			break;
		
		case CIF:
			proposicion_seleccion(folset);
			break;
		
		case CIN:
		case COUT:
			proposicion_e_s(folset);
			break;
		
		case CMAS:
		case CMENOS:
		case CIDENT:
		case CPAR_ABR:
		case CNEG:
		case CCONS_ENT:
		case CCONS_FLO:
		case CCONS_CAR:
		case CCONS_STR:
		case CPYCOMA:
			proposicion_expresion(folset);
			break;
		
		case CRETURN:
			ocurrio_retorno_g = true; 
			if(tipo_decl_g == VOID)
				error_handler(89); // Error 89: Un procedimiento no lleva sentencia de retorno

			proposicion_retorno(folset);
			break;
		
		default:
			error_handler(26); // Error 26: En Proposicion
	}
}

void proposicion_iteracion(set folset)
{
	enum Tipo tipo = ERROR; 

	match(CWHILE, 27); // Error 27: Falta while

	match(CPAR_ABR, 20); // Error 20: Falta (

	tipo = expresion(folset | CPAR_CIE | First_proposicion);
	if(!es_operable(tipo))
		error_handler(97); // Error 97: Las condiciones de las prop. de selección e iteración solo pueden ser de tipo char, int y float

	match(CPAR_CIE, 21); // Error 21: Falta )

	proposicion(folset);
}

void proposicion_seleccion(set folset)
{
	enum Tipo tipo = ERROR; 

	match(CIF, 28); // Error 28: Falta if

	match(CPAR_ABR, 20); // Error 20: Falta (

	tipo = expresion(folset | CPAR_CIE | First_proposicion | CELSE);
	if(!es_operable(tipo))
		error_handler(97); // Error 97: Las condiciones de las prop. de seleccion e iteracion solo pueden ser de tipo char, int y float

	match(CPAR_CIE, 21); // Error 21: Falta )

	proposicion(folset | CELSE);

	if(lookahead_in(CELSE))
	{
		scanner();
		proposicion(folset);
	}
}

void proposicion_e_s(set folset)
{
	enum Tipo tipo; 
	switch(lookahead())
	{
		case CIN:
			scanner();
			
			match(CSHR, 30); // Error 30: Falta >>
			
			tipo = variable(folset | CSHR | CPYCOMA);
			if(!es_operable(tipo))
				error_handler(95);  // Error 95: Las proposiciones de E/S solo aceptan variables y/o expresiones de tipo char, int y float
			
			test(folset | CSHR | CPYCOMA, First_variable, 109);	// Error 109: Símbolo inesperado en proposición de entrada 
			while(lookahead_in(CSHR | First_variable))
			{
				match(CSHR, 30);
				tipo = variable(folset | CSHR | CPYCOMA);
				if(es_operable(tipo))
				       error_handler(95); 

				test(folset | CSHR | CPYCOMA, First_variable, 109);	
			}

			match(CPYCOMA, 23); // Error 23: Falta ;
			
			break;
		
		case COUT:
			scanner();

			match(CSHL, 31); // Error 31: Falta << 
			
			tipo = expresion(folset | CSHL | CPYCOMA);
			if(!es_operable(tipo) && tipo != STRING)
				error_handler(95);

			test(folset | CSHL | CPYCOMA, First_expresion, 110); // Error 110: Símbolo inesperado en proposición de salida 
			while(lookahead_in(CSHL | First_expresion))
			{
				match(CSHL, 31); 
				tipo = expresion(folset | CSHL | CPYCOMA);
				if(!es_operable(tipo) && tipo != STRING)
					error_handler(95); 

				test(folset | CSHL | CPYCOMA, First_expresion, 110); 
			}

			match(CPYCOMA, 23); // Error 23: Falta ; 
			
			break;
		default:
			error_handler(29); // ERROR 29: Falta cin o cout }
	}
	test(folset, NADA, 53); // Error 53: Símbolo inesperado despues de proposicion entrada - salida
}

void proposicion_retorno(set folset)
{
	enum Tipo expt = VOID; 
	scanner(); 
	
	expt = expresion(folset | CPYCOMA);

	if(expt != tipo_decl_g)
		error_handler(87); // Error 87: El tipo del valor de retorno no coincide con el tipo de la funcion

	match(CPYCOMA, 23); // Error 23: Falta ; 
	test(folset, NADA, 54); // Error 54: Simbolo inesperado despues de proposicion retorno
}

void proposicion_expresion(set folset)
{
	if(lookahead_in(CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG | CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR))
		expresion(folset | CPYCOMA);

	match(CPYCOMA, 23); // Error 23: Falta ; 
	test(folset, NADA, 55); //Error 55: Simbolo inesperado despues de proposicion expresion 
}

enum Tipo expresion(set folset)
{
	Retorno_exp_simple exps; 
	enum Tipo tipo = ERROR; 
	bool op_asignacion   = false,
	     es_variable     = false; 	

	exps = expresion_simple(folset | CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG);
	es_variable = exps.es_variable;
	tipo = exps.tipo; 

	test(folset | CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG, First_expresion_simple, 111); //Error 111: Símbolo inesperado en expresion. Quizás quizo escribir '=' '!=' '==' '<' '<=' '>' o '>=' 
	while(lookahead_in(CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG | First_expresion_simple)) // En la gramática BNFE se invoca a <relación>
	{
		switch(lookahead())
		{
			case CASIGNAC:
				op_asignacion = true; 	
				scanner(); 
				break; 

			case CDISTINTO:
			case CIGUAL:
			case CMENOR:
			case CMEIG:
			case CMAYOR:
			case CMAIG:
				scanner();
				op_asignacion = false; 
				es_variable = false; 
				break;
			default:
				error_handler(65);

		}
		exps = expresion_simple(folset | CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG);

		if(op_asignacion && !es_variable){
		      	error_handler(82); // Error 82: En el lado izquierdo de una asignación debe haber una variable   
			tipo = ERROR; 	
		}
		else if(op_asignacion && es_variable){
			if(tipo == ARR || exps.tipo == ARR){
				error_handler(81); // Error 81: No se permite la asignación de arreglos como un todo 	
				tipo = ERROR; 
			}	
			else if(!es_operable(tipo)){
				error_handler(102); // Error 102: Variable del lado izquierdo de asignación no es de tipo char, int, float
				tipo = ERROR;
			}
			else if(!es_operable(exps.tipo)){
				error_handler(117); // Error 117: Expresión del lado derecho de asignación no es de tipo char, int, float
				tipo = ERROR; 	
			}
			// tipo, exps en {CHAR, INT, FLOAT}
			else if(es_menor(tipo, exps.tipo)){
				error_handler(101); // Error 101: Solo se pueden realizar coersiones a tipos mas grandes			
				tipo = ERROR; 
			}
		}	
		else{ // op < 
			if(!es_operable(tipo) || !es_operable(exps.tipo)){
				error_handler(96); // Error 96: Los operandos de los operadores logicos o relacionales solo pueden ser de tipo char, int o float
				tipo = ERROR; 	
			} // x  
			else if(tipo != exps.tipo){
				error_handler(104); // Error 104: Los operandos de los operadores logicos o aritmeticos deben ser del mismo tipo			
				tipo = ERROR; 	
			}
		}

		es_variable = es_variable && exps.es_variable; 
		test(folset | CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG, First_expresion_simple, 111); 
	}  

	return tipo; 
}

Retorno_exp_simple expresion_simple(set folset)
{
	Retorno_exp_simple exp; 
	Retorno_termino   term;	
	bool op_unario = false; 

	test(CMAS | CMENOS | First_termino, folset | CMAS | CMENOS | COR, 56); // Error 56: Simbolo inesperado o falta simb. al comienzo de expresion simple

	if(lookahead_in(CMAS | CMENOS)){
		scanner();
		exp.es_variable = false;	
		op_unario = true; 
	}

	term = termino(folset | CMAS | CMENOS | COR); 
	exp.es_variable = term.es_variable && !op_unario;

	if(op_unario && !es_operable(term.tipo)){
	       	error_handler(103); // Los operandos de los operadores logico/aritmeticos solo pueden ser de tipo char, int o float  	
		exp.tipo = ERROR;	
	}
	else
		exp.tipo = term.tipo; 

	test(folset | CMAS | CMENOS | COR, First_termino, 112); // Error 112: Símbolo inesperado en expresion simple. Quizas quizo escribir '+' '-' o '|'  
	while(lookahead_in(CMAS | CMENOS | COR | First_termino))
	{
		switch(lookahead()){
			case CMAS:
			case CMENOS:
			case COR:
				scanner();
				break;
			default:
				error_handler(65);
		}	
		term = termino(folset | CMAS | CMENOS| COR);

		if(!es_operable(exp.tipo) || !es_operable(term.tipo)){
		       	error_handler(103); // Los operandos de los operadores logico/aritmeticos solo pueden ser de tipo char, int o float	
			exp.tipo = ERROR; 
		}	
		else if(exp.tipo != term.tipo){
			error_handler(104); // Error 104: Los operandos de los operadores logicos o aritmeticos deben ser del mismo tipo			
			exp.tipo = ERROR; 	
		}
			
		exp.es_variable = false;

		test(folset | CMAS | CMENOS | COR, First_termino, 112); 
	}
	
	return exp;  
}

Retorno_termino termino(set folset)
{	
	Retorno_termino term; 
	Retorno_factor  fact = factor(folset | CMULT | CDIV | CAND);		

	term.es_variable = fact.es_variable;  
	term.tipo = fact.tipo; 

	test(folset | CMULT | CDIV | CAND, First_factor, 113); // Error 113: Símbolo inesperado en termino. Quizás quizo escribir '*' '/' o '&&' 
	while(lookahead_in(CMULT | CDIV | CAND | First_factor))
	{
		switch(lookahead()){
			case CMULT:
			case CDIV:
			case CAND:
				scanner();
				break;
			default:
				error_handler(65); 
		}	
		fact = factor(folset | CMULT | CDIV | CAND);
		
		if(!es_operable(term.tipo) || !es_operable(fact.tipo)){
			error_handler(103); // Error 103: Los operandos de los operadores logicos o aritmeticos  solo pueden ser de tipo char, int o float 
			term.tipo = ERROR; 	
		}
		else if(term.tipo != fact.tipo){
			error_handler(104); // Error 104: Los operandos de los operadores logicos o aritmeticos deben ser del mismo tipo			
			term.tipo = ERROR; 	
		}

		term.es_variable = false; 
		test(folset | CMULT | CDIV | CAND, First_factor, 113);
	}

	return term; 
}

Retorno_factor factor(set folset)
{
	Retorno_factor fact; 
	int clase_ident = CLASVAR; 
	
	fact.es_variable = false; 
	fact.tipo = ERROR; // provisional

	test(CIDENT | First_constante | CCONS_STR | CPAR_ABR | CNEG, folset, 57); // Error 57: Simbolo inesperado o falta simb. al comienzo de factor
	switch(lookahead())
	{
		case CIDENT:
			clase_ident = Clase_Ident(sbol->lexema); // Devuelve NIL, CLASFUNC, CLASVAR, CLASPAR
			if(clase_ident == CLASFUNC)
				fact.tipo = llamada_funcion(folset);		
			else{ 
				fact.tipo = variable(folset); 
				fact.es_variable = true;	
			}
			break;	

		case CCONS_ENT:
		case CCONS_FLO:
		case CCONS_CAR:
			fact.tipo = constante(folset);
			break;
		
		case CCONS_STR:
			scanner();
			fact.tipo = STRING; 
			break;
		
		case CPAR_ABR:
			scanner();	
			fact.tipo = expresion(folset | CPAR_CIE);
			match(CPAR_CIE, 21); // Error 21: Falta )
			break;
			
		case CNEG:
			scanner();//!<Expresion>
			fact.tipo = expresion(folset);
			if(!es_operable(fact.tipo)){
			       	error_handler(96); // Error 96: Los operandos de los operadores logicos o relacionales solo pueden ser de tipo char, int o float 
				fact.tipo = ERROR; 	
			}	
			break;
		default:
			error_handler(32); // Error 32: En Factor
	}
	test(folset, NADA, 58); // Error 58: Simbolo inesperado despues de factor

	return fact; 
}

enum Tipo variable(set folset)
{
	test(CIDENT, folset | CCOR_ABR, 59); // Error 59: Simbolo inesperado o falta simb. al comienzo de variable

	enum Tipo tipo = ERROR; 
	int i = en_tabla(sbol->lexema), clase; 
	
	if(i == NIL)
		error_handler(71); // Error 71: Identificador no declarado	
	else{ // Recupero si o si CLASVAR o CLASPAR	
		int j = ts[i].ets->ptr_tipo; 
		tipo = string_tipo(ts[j].ets->nbre);
		clase = ts[i].ets->clase;
	}
		// Decision: Identificadores no declarados no los damos de alta.

	match(CIDENT, 17); // Error 17: Falta identificador

	if(lookahead_in(CCOR_ABR))
	{ 
		scanner();	
		expresion(folset | CCOR_CIE);
		match(CCOR_CIE, 22); // Error 22: Falta ]

		if(i != NIL && tipo != ARR){
			error_handler(78); // Error 78: La variable no es de tipo arreglo			
			tipo = ERROR;	
		}
		else if(tipo == ARR){
			int j; 
			if(clase == CLASVAR)
				j = ts[i].ets->desc.part_var.arr.ptero_tipo_base;		
			else
				j = ts[i].ets->desc.part_var.param.ptero_tipo_base;	
			tipo = string_tipo(ts[j].ets->nbre); 
		}
	}

	test(folset, NADA, 60); // Error 60: Simbolo inesperado despues de variable  
	
	return tipo; 
}

// Clase = Funcion => Lo Encontró. 
enum Tipo llamada_funcion(set folset)
{
	int i = en_tabla(sbol->lexema),
	    cant_par_inv  = 0,
	    cant_par_decl = ts[i].ets->desc.part_var.sub.cant_par; 

	int j = ts[i].ets->ptr_tipo; 
	enum Tipo tipo = string_tipo(ts[j].ets->nbre);

	match(CIDENT, 34); // Error 34: Falta identificador de funcion
	
	match(CPAR_ABR, 20); // Error 20: Falta (
	
	if(lookahead_in(First_lista_expresiones))
		cant_par_inv = lista_expresiones(folset | CPAR_CIE);

	match(CPAR_CIE, 21); // Error 21: Falta )

	if(cant_par_decl != cant_par_inv)
		error_handler(90); // Error 90: La CANTIDAD de parametros actuales no coincide con la cantidad de parametros formales

	test(folset, NADA, 61); // Error 61: Simbolo inesperado despues de llamada a funcion

	return tipo; 
}


int lista_expresiones(set folset)
{
	int cant_par = 0; 

	expresion(folset | CCOMA);
	cant_par += 1;

	test(folset | CCOMA, First_expresion, 114);// Error 114: Símbolo inesperado en lista de expresiones. Quizás quizo escribir ','
	while(lookahead_in(CCOMA | First_expresion))
	{
		match(CCOMA, 64); // Error 64: Falta ,
		expresion(folset | CCOMA);
		test(folset | CCOMA, First_expresion, 114);

		cant_par += 1; 
	}

	return cant_par;
}

enum Tipo constante(set folset)
{ 
	enum Tipo tipo; 

	test(CCONS_ENT | CCONS_FLO | CCONS_CAR, folset, 62); // Error 62: Símbolo inesperado o falta simb. al comienzo de constante
	switch(lookahead())
	{
		case CCONS_ENT:
			scanner();
			tipo = INT;
			break;
		
		case CCONS_FLO:
			scanner();
			tipo = FLOAT;
			break;
		
		case CCONS_CAR:
			scanner();
			tipo = CHAR;
			break;
		
		default:
			tipo = ERROR; 
			error_handler(33); // Error 33: Falta constante
	}
	test(folset, NADA, 63); // Error 63: Símbolo inesperado después de constante.

	return tipo;
}
