#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codigos.h"
#include "util.h"
#include "error.h"

int last_call=0;

/*********** prototipos *************/

void unidad_traduccion(); 		// <unidad de traducción> 
void declaraciones();      		// <declaraciones> 
void especificador_tipo(); 		// <especificador de tipo> 
void especificador_declaracion(); 	// <especificador de declaración> 
void definicion_funcion();		// <definición de función> 
void declaracion_variable();		// <declaración de variable>
void lista_declaraciones_param();	// <lista declaración de parámetros> 
void declaracion_parametro();		// <declaración de parámetro> 
void declarador_init();			// <declarador init> 
void lista_declaraciones_init();	// <lista declaraciones init> 
void lista_inicializadores(); 		// <lista de inicializadores> 
void lista_proposiciones();		// <lista de proposiciones> 
void lista_declaraciones();		// <lista de declaraciones> 
void declaracion();			// <declaración> 
void proposicion();			// <proposición> 
void proposicion_expresion();		// <proposición expresión> 
void proposicion_compuesta();		// <proposición compuesta>
void proposicion_seleccion();		// <proposición de selección> 
void proposicion_iteracion();		// <proposición de iteración>
void proposicion_e_s();			// <proposición de entrada/salida>
void proposicion_retorno();		// <proposición de retorno> 
void expresion();			// <expresión> 
void expresion_simple();		// <expresión simple> 
void termino();				// <término> 
void factor();				// <factor> 
void variable();			// <variable> 
void llamada_funcion();			// <llamada a función> 
void lista_expresiones();		// <lista de expresiones> 
void constante();			// <constante> 


/*
 *	De la gramática BNFE falta <relación> 
 * */
