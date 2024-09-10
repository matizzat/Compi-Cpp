#define First_variable           CIDENT
#define First_declarador_init    CASIGNAC | CCOR_ABR
#define First_declaracion 	 CVOID | CCHAR | CINT | CFLOAT
#define First_lista_declaraciones_init CIDENT
#define First_lista_declaraciones CVOID | CCHAR | CINT | CFLOAT
#define First_lista_proposiciones CMAS | CMENOS | CIDENT | CCONS_ENT | CCONS_FLO | CCONS_CAR | CNEG | CPAR_ABR | CCONS_STR | CPYCOMA | CLLA_ABR | CWHILE | CIF | CRETURN | CIN | COUT
#define First_proposicion 	CMAS | CMENOS | CIDENT | CCONS_ENT | CCONS_FLO | CCONS_CAR | CNEG | CPAR_ABR | CCONS_STR | CPYCOMA | CLLA_ABR | CWHILE | CIF | CRETURN | CIN | COUT
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

/**/

// Ok
void test(set c1, set c2, int ne){
	if(!lookahead_in(c1)){
		error_handler(ne); 			
		while(!lookahead_in(c1 | c2))
			scanner(); 	
	}
}

/********* funciones del parser ***********/

// Ok
void unidad_traduccion(set folset)
{
	test(folset | CVOID | CCHAR | CINT | CFLOAT, NADA, 41); // Simbolo inesperado o falta especificador de tipo
	while(lookahead_in(CVOID | CCHAR | CINT | CFLOAT)){
		declaraciones(folset | CVOID | CCHAR | CINT | CFLOAT);
		test(folset | CVOID | CCHAR | CINT | CFLOAT, NADA, 41); 
	}
}


// Ok
void declaraciones(set folset)
{	
	especificador_tipo(folset | CIDENT | CPAR_ABR | CASIGNAC | CCOR_ABR | CCOMA | CPYCOMA);
	
	match(CIDENT, 17); // Error 17: Falta identificador
	
	especificador_declaracion(folset);
}

// Ok
void especificador_tipo(set folset)
{
	test(CVOID | CCHAR | CINT | CFLOAT, folset, 41); // Error 41: Simbolo inesperado o falta especificador de tipo	
	switch(lookahead())
	{
		case CVOID:
			scanner();
			break;
			
		case CCHAR:
			scanner();
			break;
			
		case CINT:
			scanner();
			break;
			
		case CFLOAT:
			scanner();
			break;
			
		default:
			error_handler(18); // Error 18: Tipo no definido
	}
	test(folset, NADA, 42); // Error 42: Simbolo inesperado despues de especificador de tipo 
}

// Ok
void especificador_declaracion(set folset)
{
	test(CPAR_ABR | CASIGNAC | CCOR_ABR | CCOMA | CPYCOMA, folset, 43); 	// Error 43: Simbolo inesperado o falta simb. al comienzo de especif. de declaracion
	switch(lookahead())
	{
		case CPAR_ABR:
			definicion_funcion(folset);
			break;
		
		case CASIGNAC:
		case CCOR_ABR:
		case CCOMA:
		case CPYCOMA:
			declaracion_variable(folset);
			break;
		
		default:
			error_handler(19); // Error 19: En Especificador de Declaración
	}
}

// Ok
void definicion_funcion(set folset) 
{ 
	match(CPAR_ABR, 20); // Error 20: Falta (

	if(lookahead_in(CVOID | CCHAR | CINT | CFLOAT))
		lista_declaraciones_param(folset | CPAR_CIE | CLLA_ABR);

	match(CPAR_CIE, 21); // Error 21: Falta )

	proposicion_compuesta(folset);
}

// Ok
void lista_declaraciones_param(set folset)
{
	declaracion_parametro(folset | CCOMA);
	test(folset | CCOMA, CVOID | CCHAR | CINT | CFLOAT, 37);  // Error 37: Símbolo incorrecto dentro de lista decl. parámetros.
	while(lookahead_in(CCOMA | CVOID | CCHAR | CINT | CFLOAT))
	{
		match(CCOMA, 64); // Error 64: Falta ,  
		declaracion_parametro(folset | CCOMA);
		test(folset | CCOMA, CVOID | CCHAR | CINT | CFLOAT, 37); 	
	}
}

// Ok
void declaracion_parametro(set folset)
{
	especificador_tipo(folset | CAMPER | CIDENT | CCOR_ABR);

	if(lookahead_in(CAMPER))
		scanner();

	match(CIDENT, 17); // Error 17: Falta identificador

	if(lookahead_in(CCOR_ABR))
	{
		scanner();
		match(CCOR_CIE, 22); // Error 22: Falta ]
	}
	test(folset, NADA, 45); // Error 45: Simbolo inesperado despues de declarar un parametro
}

// Ok
void lista_declaraciones_init(set folset)
{
	test(CIDENT, folset | First_declarador_init | CCOMA, 46); // Error 46: Simbolo inesperado al comienzo de lista decl. init
	match(CIDENT, 17); // Error 17: Falta identificador

	declarador_init(folset | CCOMA);
	test(folset | CCOMA, CIDENT | CCOMA | First_declarador_init, 72); // Error 72: Se espera lista de variables o lista de variables inicializadas;
	while(lookahead_in(CCOMA | CIDENT | First_declarador_init))
	{
		match(CCOMA, 64); // Error 64: Falta , 	
		match(CIDENT, 17); // Error 17: Falta identificador
		declarador_init(folset | CCOMA);
		test(folset | CCOMA, CIDENT | CCOMA | First_declarador_init, 72); // Error 72: Se espera lista de variables o lista de variables inicializadas; 
	}
}

// Ok
void declaracion_variable(set folset)
{
	declarador_init(folset | CCOMA | CPYCOMA);

	if(lookahead_in(CCOMA))
	{
		scanner();
		lista_declaraciones_init(folset | CPYCOMA);
	}

	match(CPYCOMA, 23); // Error 23: Falta ; 
	test(folset,NADA,10); // ---
}


// Ok
void declarador_init(set folset)
{
	test(folset | CASIGNAC | CCOR_ABR, CCOR_CIE, 47); // Error 47: Simbolo inesperado al comienzo de declarador init
	switch(lookahead())
	{
		case CASIGNAC:
			scanner();
			constante(folset);
			break;

		case CCOR_ABR:
		case CCOR_CIE:
			match(CCOR_ABR, 22); // Error 22: Falta ]	

			if(lookahead_in(CCONS_ENT)) // Por qué no Match? 
				constante(folset | CCOR_CIE | CASIGNAC);

			match(CCOR_CIE, 22); // Error 22: Falta ]

			if(lookahead_in(CASIGNAC))
			{
				scanner();
				match(CLLA_ABR, 24); // Error 24: Falta { 
				lista_inicializadores(folset | CLLA_CIE);
				match(CLLA_CIE, 25); // Error 25: Falta } 
			}
			break;
	}
	test(folset, NADA, 48); // Error 48: Simbolo inesperado despues de declarador init 
}

// Ok
void lista_inicializadores(set folset)
{
	constante(folset | CCOMA);
	test(folset | CCOMA, First_constante, 73); // Error 73: Se espera una constante o una lista de constantes separadas por , .
	while(lookahead_in(CCOMA | First_constante))
	{
		match(CCOMA, 23); // Error 23: Falta ;	
		constante(folset | CCOMA);
		test(folset | CCOMA, First_constante, 73); // Error 73: Se espera una constante o una lista de constantes separadas por , .
	}
}

// Ok
void proposicion_compuesta(set folset)
{
	test(CLLA_ABR, folset | First_lista_declaraciones | First_lista_proposiciones | CLLA_CIE, 49); // Error 49: Simbolo inesperado o falta simb. al comienzo de proposicion compuesta
	match(CLLA_ABR, 24); // Error 24: Falta { 

	if(lookahead_in(CVOID | CCHAR | CINT | CFLOAT))
		lista_declaraciones(folset | First_lista_proposiciones | CLLA_CIE);

	if(lookahead_in(CLLA_ABR | CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG |
						 CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR |
						 CIF | CWHILE | CIN | COUT | CPYCOMA | CRETURN))
		lista_proposiciones(folset | CLLA_CIE);

	match(CLLA_CIE, 25); // Error 25: Falta } 
	test(folset, NADA, 50); // Error 50: Símbolo inesperado despues de proposicion compuesta
}

// OK
void lista_declaraciones(set folset)
{
	declaracion(folset | First_declaracion); 
	test(folset | First_declaracion, NADA, 70); // Error 70: Se espera un especificador de tipo en lista de declaraciones"
	while(lookahead_in(CVOID | CCHAR | CINT | CFLOAT)){
		declaracion(folset | First_declaracion);	
		test(folset | First_declaracion, NADA, 70); // Error 70: Se espera un especificador de tipo en lista de declaraciones"
	}
}

// OK
void declaracion(set folset)
{
	especificador_tipo(folset | First_lista_declaraciones_init | CPYCOMA);

	lista_declaraciones_init(folset | CPYCOMA);

	match(CPYCOMA, 23); // Error 23: Falta ;
	test(folset, NADA, 51); // Error 51: Simbolo inesperado despues de declaracion
}

// Ok
void lista_proposiciones(set folset)
{
	proposicion(folset | First_proposicion);
	test(folset | First_proposicion, NADA, 71); // Error 71: Se espera una proposicion en lista de proposiciones
	while(lookahead_in(First_proposicion)){
		proposicion(folset | First_proposicion);
		test(folset | First_proposicion, NADA, 71); // Error 71: Se espera una proposicion en lista de proposiciones
	}
}

// Ok
void proposicion(set folset)
{
	test(CLLA_ABR | CWHILE | CIF | CIN | COUT | First_proposicion_expresion | CRETURN, folset, 52); // Error 52: Simbolo inesperado o falta simb. al comienzo de proposicion
	switch(lookahead())
	{
		case CLLA_ABR:
			proposicion_compuesta(folset);
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
			proposicion_retorno(folset);
			break;
		
		default:
			error_handler(26); // Error 26: En Proposicion
	}
}

// Ok
void proposicion_iteracion(set folset)
{
	match(CWHILE, 27); // Error 27: Falta while

	match(CPAR_ABR, 20); // Error 20: Falta (

	expresion(folset | CPAR_CIE | First_proposicion);

	match(CPAR_CIE, 21); // Error 21: Falta )

	proposicion(folset);
}

// Ok
void proposicion_seleccion(set folset)
{
	match(CIF, 28); // Error 28: Falta if

	match(CPAR_ABR, 20); // Error 20: Falta (

	expresion(folset | CPAR_CIE | First_proposicion | CELSE);

	match(CPAR_CIE, 21); // Error 21: Falta )

	proposicion(folset | CELSE);

	if(lookahead_in(CELSE))
	{
		scanner();
		proposicion(folset);
	}
}


// Ok
void proposicion_e_s(set folset)
{
	switch(lookahead())
	{
		case CIN:
			scanner();
			
			match(CSHR, 30); // Error 30: Falta >>
			
			variable(folset | CSHR | CPYCOMA);
			test(folset | CSHR | CPYCOMA, First_variable, 74);	// Error 74: se espera >> en proposicion de entrada / salida
			while(lookahead_in(CSHR | First_variable))
			{
				match(CSHR, 30);
				variable(folset | CSHR | CPYCOMA);
				test(folset | CSHR | CPYCOMA, First_variable, 74);	// Error 74: se espera >> en proposicion de entrada / salida
			}

			match(CPYCOMA, 23); // Error 23: Falta ;
			
			break;
		
		case COUT:
			scanner();

			match(CSHL, 31); // Error 31: Falta << 
			
			expresion(folset | CSHL | CPYCOMA);
			test(folset | CSHL | CPYCOMA, First_expresion, 75); // Error 75: Se espera << en proposicion de entrada / salida
			while(lookahead_in(CSHL | First_expresion))
			{
				match(CSHL, 31); 
				expresion(folset | CSHL | CPYCOMA);
				test(folset | CSHL | CPYCOMA, First_expresion, 75); // Error 75: Se espera << en proposicion de entrada / salida
			}

			match(CPYCOMA, 23); // Error 23: Falta ; 
			
			break;
		default:
			error_handler(29); // ERROR 29: Falta cin o cout }
	}
	test(folset, NADA, 53); // Error 53: Símbolo inesperado despues de proposicion entrada - salida
}

// Ok
void proposicion_retorno(set folset)
{
	scanner(); // Por qué no Match? Por qué es invocación condicional? 
	
	expresion(folset | CPYCOMA);
	
	match(CPYCOMA, 23); // Error 23: Falta ; 
	test(folset, NADA, 54); // Error 54: Simbolo inesperado despues de proposicion retorno
}

// Ok
void proposicion_expresion(set folset)
{
	if(lookahead_in(CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG | CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR))
		expresion(folset | CPYCOMA);

	match(CPYCOMA, 23); // Error 23: Falta ; 
	test(folset, NADA, 55); //Error 55: Simbolo inesperado despues de proposicion expresion 
}

// Ok
void expresion(set folset)
{	
	expresion_simple(folset | CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG);
	test(folset | CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG, NADA, 76); //Error 76: Se espera una asignacion o un operador relacional en esta expresion
	while(lookahead_in(CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG)) // En la gramática BNFE se invoca a <relación>
	{
		switch(lookahead())
		{
			case CASIGNAC:
				scanner();
				expresion_simple(folset);
				break;
				
			case CDISTINTO:
			case CIGUAL:
			case CMENOR:
			case CMEIG:
			case CMAYOR:
			case CMAIG:
				scanner();
				expresion_simple(folset);
				break;
		}
		test(folset | CASIGNAC | CDISTINTO | CIGUAL | CMENOR | CMEIG | CMAYOR | CMAIG, NADA, 76); //Error 76: Se espera una asignacion o un operador relacional en esta expresion
	}
}

// Ok
void expresion_simple(set folset)
{
	test(CMAS | CMENOS | First_termino, folset | CMAS | CMENOS | COR, 56); // Error 56: Simbolo inesperado o falta simb. al comienzo de expresion simple
	if(lookahead_in(CMAS | CMENOS))
		scanner();

	termino(folset | CMAS | CMENOS | COR);
	test(folset | CMAS | CMENOS | COR, NADA, 77); // Error 77: Se espera otro termino en esta expresion simple
	while(lookahead_in(CMAS | CMENOS | COR))
	{
		scanner();
		termino(folset | CMAS | CMENOS| COR);
	       	test(folset | CMAS | CMENOS | COR, NADA, 77); // Error 77: Se espera otro termino en esta expresion simple
	}
}

// Ok
void termino(set folset)
{	
	factor(folset | CMULT | CDIV| CAND);
	test(folset | CMULT | CDIV | CAND, NADA, 78); // Error 78: Se espera otro factor en este termino
	while(lookahead_in(CMULT | CDIV | CAND))
	{
		scanner();
		factor(folset | CMULT | CDIV | CAND);
		test(folset | CMULT | CDIV | CAND, NADA, 78); // Error 78: Se espera otro factor en este termino
	}
}

// OK
void factor(set folset)
{
	test(CIDENT | First_constante | CCONS_STR | CPAR_ABR | CNEG, folset | CPAR_CIE, 57); // Error 57: Simbolo inesperado o falta simb. al comienzo de factor
	switch(lookahead())
	{
		case CIDENT:
			/***************** Re-hacer *****************/
			if(sbol->lexema[0] == 'f')
				llamada_funcion(folset);
			else
				variable(folset);
			/********************************************/
			/* El alumno debera evaluar con consulta a TS
			si bifurca a variable o llamada a funcion */
			break;
		
		case CCONS_ENT:
		case CCONS_FLO:
		case CCONS_CAR:
			constante(folset);
			break;
		
		case CCONS_STR:
			scanner();
			break;
		
		case CPAR_ABR:
		case CPAR_CIE:
			scanner();
			expresion(folset | CPAR_CIE);
			match(CPAR_CIE, 21); // Error 21: Falta )
			break;
			
		case CNEG:
			scanner();
			expresion(folset);
			break;
			
		default:
			error_handler(32); // Error 32: En Factor
	}
	test(folset, NADA, 58); // Error 58: Simbolo inesperado despues de factor
}

// Ok
void variable(set folset)
{
	test(CIDENT, folset | CCOR_ABR, 59); // Error 59: Simbolo inesperado o falta simb. al comienzo de variable
	match(CIDENT, 17); // Error 17: Falta identificador

	/* El alumno debera verificar con una consulta a TS
	si, siendo la variable un arreglo, corresponde o no
	verificar la presencia del subindice */

	if(lookahead_in(CCOR_ABR))
	{ 
		scanner();
		expresion(folset | CCOR_CIE);
		match(CCOR_CIE, 22); // Error 22: Falta ]
	}
	test(folset, NADA, 60); // Error 60: Simbolo inesperado despues de variable  
}

// Ok
void llamada_funcion(set folset)
{
	match(CIDENT, 34); // Error 34: Falta identificador de funcion
	
	match(CPAR_ABR, 20); // Error 20: Falta (
	
	if(lookahead_in(First_lista_expresiones))
		lista_expresiones(folset | CPAR_CIE);

	match(CPAR_CIE, 21); // Error 21: Falta )

	test(folset, NADA, 61); // Error 61: Simbolo inesperado despues de llamada a funcion
}


// Ok
void lista_expresiones(set folset)
{
	expresion(folset | CCOMA);
	test(folset | CCOMA, First_expresion, 79);// Error 79: Se espera una expresion o una lista de expresiones separadas por , .
	while(lookahead_in(CCOMA | First_expresion))
	{
		match(CCOMA, 64); // Error 64: Falta ,
		expresion(folset | CCOMA);
		test(folset | CCOMA, First_expresion, 79); // Error 79: Se espera una expresion o una lista de expresiones separadas por , .
	}
}

// Ok
void constante(set folset)
{ 
  	test(CCONS_ENT | CCONS_FLO | CCONS_CAR, folset, 62); // Error 62: Símbolo inesperado o falta simb. al comienzo de constante
	switch(lookahead())
	{
		case CCONS_ENT:
			scanner();
			break;
		
		case CCONS_FLO:
			scanner();
			break;
		
		case CCONS_CAR:
			scanner();
			break;
		
		default:
			error_handler(33); // Error 33: Falta constante
	}
	test(folset, NADA, 63); // Error 63: Símbolo inesperado después de constante.
}
