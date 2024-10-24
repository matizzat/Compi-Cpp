#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h>
#include "codigos.h"
#include "util.h"
#include "error.h"
#include "ts.h"
#include "tipo.h" 

int last_call=0;

/*********** tipos retorno **********/ 
typedef struct{
	bool es_variable; 
	enum Tipo tipo;  
} Retorno_factor; 

typedef struct{
	bool es_variable; 
	enum Tipo tipo; 	
} Retorno_termino; 

typedef struct{
	bool es_variable;
	enum Tipo tipo; 
} Retorno_exp_simple; 

/*********** atributos globales *****/

bool ocurrio_retorno_g = false;
enum Tipo tipo_decl_g = ERROR; 

/*********** prototipos *************/

void unidad_traduccion(); 						// <unidad de traducción> 
bool declaraciones();      						// <declaraciones> 
enum Tipo especificador_tipo(); 					// <especificador de tipo> 
bool especificador_declaracion(set, enum Tipo tipo, char* nombre); 	// <especificador de declaración> 
void definicion_funcion(set, enum Tipo tipo, char* nombre);		// <definición de función> 
void declaracion_variable(set, enum Tipo tipo, char* nombre);		// <declaración de variable>
int lista_declaraciones_param();					// <lista declaración de parámetros> 
void declaracion_parametro();						// <declaración de parámetro> 
void declarador_init(set, enum Tipo tipo, char* nombre);		// <declarador init> 
void lista_declaraciones_init(set, enum Tipo tipo);			// <lista declaraciones init> 
int  lista_inicializadores(set, enum Tipo tipo); 			// <lista de inicializadores> 
void lista_proposiciones();						// <lista de proposiciones> 
void lista_declaraciones();						// <lista de declaraciones> 
void declaracion();							// <declaración> 
void proposicion();							// <proposición> 
void proposicion_expresion();						// <proposición expresión> 
void proposicion_compuesta(set, bool vengo_de_prop);			// <proposición compuesta>
void proposicion_seleccion();						// <proposición de selección> 
void proposicion_iteracion();				// <proposición de iteración>
void proposicion_e_s();					// <proposición de entrada/salida>
void proposicion_retorno();				// <proposición de retorno> 
enum Tipo expresion();					// <expresión> 
Retorno_exp_simple expresion_simple();			// <expresión simple> 
Retorno_termino termino();				// <término> 
Retorno_factor factor();				// <factor> 
enum Tipo variable();					// <variable> 
enum Tipo llamada_funcion();				// <llamada a función> 
int lista_expresiones();				// <lista de expresiones> 
enum Tipo constante();					// <constante> 
