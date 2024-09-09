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

void func){}; // falta (

void func({}; // falta )

void func(int){}; // falta identificador de param

void func(param){}; // falta tipo de param

void func(int &){}; // falta identificador de param

void func(&arr){}; // falta tipo de param

void func(&arr){}; // falta tipo de param

void func(int arr]){}; // falta ]

void func(int arr]){}; // falta [

void func(int &arr]){}; // falta [

void func(int &arr[){}; // falta ]

void func(int a, ){}; // se espera tipo despues de la coma

void func(int a, int){}; // se espera ident despues de tipo

void func(int a, b){}; // se espera tipo para el param

void func(int a, b, int c){}; // se espera tipo para el param

void func(int &a, int b[, float c){}; // se espera ]

void func(int &a, int b], float c){}; // se espera [

void func(int &a[, float b, float c]){}; // se espera [ y ver como se recupera para el 3er param

float func() {
int ;
int b = 8;
}// se espera ident

void func() {
;int b = 8;
}// se espera tipo ?


void func() {
b;
}// aca no sabe si quiero probar declaracion sin tipo o es una expresion simple. No salta error sintactico aca

void func() {
int b =;

}

void func() {
int =5;

}

void func() {
float a=1.0,b=2.4,c=6.3;
{
a=a+b;

}// falta }

void func() {

float a=1.0,b=2.4,c=6.3;
a=a+b;
}
}// falta {


void func() {
{
float a=1.0,b=2.4,c=6.3;
a=a+b;
}
}// falta {


void func() {
int i = 0;
while i<10)
i=i+1;
}// falta ( despues del while

void func() {
int i = 0;
while(i<10
i=i+1;
}// falta )


void func() {
int i = 0;
while(i<10
i=i+1;
}// falta ) sin cuerpo el while

void func() {
int i = 0;
while(1<10{
i=i+1;
}
}// falta ) sin cuerpo el while

void func() {
int i = 0;
while i<10){
i=i+1;
}
}// falta ) con cuerpo el while

void func() {
int i = 0;
while(i<10{
i=i+1;
}
}// falta ) con cuerpo el while

void func() {
int i = 0;
while i<10){
i=i+1;
}
}// falta ) con cuerpo el while

void func() {
int i = 0;
while i<10){
i=i+1;
}
}// falta ) con cuerpo el while

void func() {
int i = 0;
if i<10) a=b;
}// falta (

void func() {
int i = 0;
if (i<10 a=b;
}// falta )


void func() {
int i = 0;
if i<10){
a=b;
}
}// falta (


void func() {
int i = 0;
if i<10){
a=b;
}
}// falta (

void func() {
int i = 0;
if i<10){
a=b;
}
}
// falta (

void fmain (){
int a = 0;
while(1<2 if (!a)a=1;
}
