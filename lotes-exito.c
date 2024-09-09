int a;

int a = 5;

float values[];

float values[3];

float values[] = {2.5};

float values[] = {2.5, 3.1, 7.8};

int indexes[2] = {8};

int indexes[3] = {5,7};

int indexes[3] = {5,7,321};

void myProcedure(){}

char myFunc(){}

float myFunction(int a){}

float myFunction(int a, int b){}

void myProc(char &arr[]){}

void myProc(char &arr){}

void myProc(char arr[]){}

void myProc(char a, int &indexes[], char b, float &arr, int matrix[]){}

char myFunc(){
int a;
int a = 5;
float values[];
float values[3];
float values[] = {2.5};
float values[] = {2.5, 3.1, 7.8};
int indexes[2] = {};
int indexes[3] = {5,7};
int indexes[3] = {5,7,321};
}

//expresion -> expresion simple ... -> ... termino ... -> factor ... -> 
void myProc(){
a;
}

void myProc(){
5;
}

void myProc(){
!val;
}

void myProc(){
(-b);
}

void myProc(){
myFunc();
}


void myProc(){
"this is a string";
}

//expresion -> expresion simple ... -> ... [+|-] termino ... -> factor ....
void myProc(){
-a;
}

void myProc(){
+5;
}

void myProc(){
-!"Str";
}

void myProc(){
+(6);
}

void myProc(){
-myFunc();
}


void myProc(){
+"this is a string";
}

//expresion -> expresion simple ... -> ... termino (+| - | ||) termino-> factor ....
void myProc(){
a+b;
}

void myProc(){
5-x;
}

void myProc(){
!isLogic(-1,+4) || myFunc();
}

void myProc(){
(2.7) - 6;
}

void myProc(){
myFunc() + b;
}


void myProc(){
"this is a string" + !val;
}

//expresion -> expresion simple ... -> ... termino (+| - | ||) termino-> factor ....
void myProc(){
a+b;
}

void myProc(){
5-x;
}

void myProc(){
!(!value) || myFunc();
}

void myProc(){
( (!"str") ) - 6;
}

void myProc(){
myFunc() + b;
}


void myProc(){
"this is a string" + !val;
}

//expresion -> expresion simple ... -> ... termino -> factor (* | / | &&) factor
void myProc(){
a*myNumber(a,b);
}

void myProc(){
5/-x;
}

void myProc(){
!a && g;
}

void myProc(){
(6/5) * 6;
}

void myProc(){
myFunc() && b;
}


void myProc(){
"this is a string" / !val;
}

//expresion -> expresion simple ... -> [+/-] termino (+| - | ||) termino-> factor (* | / | &&) factor
void myProc(){
-a*5+myNumber(a,b);
}

void myProc(){
+5/!a - x&&!"constant string";
}

void myProc(){
-!a*(5+b) || aFunction(b*2, myProc());
}

void myProc(){
+(!b)/b-"as"&&"k";
}

void myProc(){
myFunc()&&another(6, 2.8, b) || (fibo(7)/!isAMalware());
}


void myProc(){
"this is a string"*4 - a/!(a-b);
}

//expresion -> expresion simple {= expresion simple | <relacion> expresion simple}
void myProc(){
-a*5+myNumber(a,b) = -a;
}

void myProc(){
+5/!a - x&&!"constant string" = myFunc()&&another(6, 2.8, b) || (fibo(7)/!isAMalware());
}

void myProc(){
-!a*(5+b) || aFunction(b*2, myProc())  == 7;
}

void myProc(){
+(!b)/b-"as"&&"k" <= 3421.5648;
}

void myProc(){
myFunc()&&another(6, 2.8, b) || (fibo(7)/!isAMalware()) != parabolicNumber(x,y,z);
}


void myProc(){

b = b*8+factorial(4);

}

//proposicion compuesta -> { [lista de declaracion] [lista de proposiciones] }
void myProc(){
int a;
int a = 5;
float val[];
float values[3];
myFunc()&&another(6, 2.8, b) || (fibo(7)/!isAMalware()) != parabolicNumber(x,y,z);
float v[] = {2.5};
float values[] = {2.5, 3.1, 7.8};
int index[2] = {};
int indexes[3] = {5,7};
+(!b)/b-"as"&&"k" <= 3421.5648;
int indexes[3] = {5,7,321};
b = b*8+factorial(4);
}

void myProc(){
int a;
int a = 5;
float val[];
float values[3];
myFunc()&&another(6, 2.8, b) || (fibo(7)/!isAMalware()) != parabolicNumber(x,y,z);
float v[] = {2.5};
float values[] = {2.5, 3.1, 7.8};
int index[2] = {};
int indexes[3] = {5,7};
+(!b)/b-"as"&&"k" <= 3421.5648;
int indexes[3] = {5,7,321};
b = b*8+factorial(4);
}


void myProc(){
int a = 5;
int b = 2;
int c;

c=a+b;

iDoACallHere(c, -a);

{
int a = b;
b = c+4;
myProc(2*a,3*b);
}
}

float myFunc(){

int a = 5;
int b = 2;
int c;

c=a+b;

float z = iDoACallHere(c, -a);

{
int a = b;
b = c+4;

myProc(2*a,3*b);
}

return z;
}

float myFunc(){

int a = 5;
int b = 2;
int c;

c=a+b;

iDoACallHere(c, -a);

{
int a = b;
b = c+4;

myProc(2*a,3*b);
}

return c;
}

void myProc() {
int i = 0;

while(i<10){
executeMyProc();
i = i+1;
}
}

void myProc() {
int i = 0;

while(i<10) executeMyProc(i);

return c;
}

void myProc() {
int a = 6, b = 7;
if(a<b) return 1;
}

void myProc() {
int a = 6, b = 7;
if(a<b) return 1 else 0;
}

void myProc() {
int a = 6, b = 7;
if(a<b){
a = !isLogic(-1,+4) || myFunc();
}
}

void myProc() {
int a = 6, b = 7;
if(a>=b){
b = !isLogic(-1,+4) || myFunc();
return b;
}
else return a;
}

void myProc() {
int a = 6, b = 7;
if(a>=b){
b = !isLogic(-1,+4) || myFunc();
return b;
}
else{
myFunc()&&another(6, 2.8, b) || (fibo(7)/!isAMalware()) != parabolicNumber(x,y,z);
float v[] = {2.5};
b = b*8+factorial(4);
return a;
}
}

int myFunc(){

int a = 5;
int b = 2;
int c;

c=a+b;

cin >> a >> b >> c;

return c;
}

int myFunc(){
cout << 5 << 8+factorial(4);
}

