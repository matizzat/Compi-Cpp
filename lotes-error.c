my_variable; // falta tipo

int; // falta identificador

int a // falta ;

float y 2.8 ; // falta =

float y = ; // falta constante

int i = 3 //falta ;

char arr]; // falta [

char arr[;// falta ]

float values []{}; //falta =

float values []=}; //falta {

float values []={; //falta }

int indexes []={}; // falta constante para inicializar dentro de las llaves

int indexes []={4,}; // falta constante despues de la ,

int indexes []={,5}; // falta constante antes de la ,

void my_proc){}; // falta (

void my_proc({}; // falta )

void my_proc(int){}; // falta identificador de param

void my_proc(param){}; // falta tipo de param

void my_proc(int &){}; // falta identificador de param

void my_proc(&arr){}; // falta tipo de param

void my_proc(&arr){}; // falta tipo de param

void my_proc(int arr]){}; // falta ]

void my_proc(int arr]){}; // falta [

void my_proc(int &arr]){}; // falta [

void my_proc(int &arr[){}; // falta ]

void my_proc(int a, ){}; // se espera tipo despues de la coma

void my_proc(int a, int){}; // se espera ident despues de tipo

void my_proc(int a, b){}; // se espera tipo para el param

void my_proc(int a, b, int c){}; // se espera tipo para el param

void my_proc(int &a, int b[, float c){}; // se espera ]

void my_proc(int &a, int b], float c){}; // se espera [

void my_proc(int &a[, float b, float c]){}; // se espera [ y ver como se recupera para el 3er param


