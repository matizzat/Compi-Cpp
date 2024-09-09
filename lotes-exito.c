int a;

int a = 5;

float values[];

float values[3];

float values[] = {2.5};

float values[] = {2.5, 3.1, 7.8};

int indexes[2] = {8};

int indexes[3] = {5,7};

int indexes[3] = {5,7,321};

void func(){}

char func(){}

float function(int a){}

float function(int a, int b){}

void func(char &arr[]){}

void func(char &arr){}

void func(char arr[]){}

void func(char a, int &indexes[], char b, float &arr, int matrix[]){}

char func(){
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
void func(){
a;
}

void func(){
5;
}

void func(){
!val;
}

void func(){
(-b);
}

void func(){
func();
}


void func(){
"this is a string";
}

//expresion -> expresion simple ... -> ... [+|-] termino ... -> factor ....
void func(){
-a;
}

void func(){
+5;
}

void func(){
-!"Str";
}

void func(){
+(6);
}

void func(){
-func();
}


void func(){
+"this is a string";
}

//expresion -> expresion simple ... -> ... termino (+| - | ||) termino-> factor ....
void func(){
a+b;
}

void func(){
5-x;
}

void func(){
!fisLogic(-1,+4) || func();
}

void func(){
(2.7) - 6;
}

void func(){
func() + b;
}


void func(){
"this is a string" + !val;
}

//expresion -> expresion simple ... -> ... termino (+| - | ||) termino-> factor ....
void func(){
a+b;
}

void func(){
5-x;
}

void func(){
!(!value) || func();
}

void func(){
( (!"str") ) - 6;
}

void func(){
func() + b;
}


void func(){
"this is a string" + !val;
}

//expresion -> expresion simple ... -> ... termino -> factor (* | / | &&) factor
void func(){
a*fmyNumber(a,b);
}

void func(){
5/x;
}

void func(){
!a && g;
}

void func(){
(6/5) * 6;
}

void func(){
func() && b;
}


void func(){
"this is a string" / !val;
}

//expresion -> expresion simple ... -> [+/-] termino (+| - | ||) termino-> factor (* | / | &&) factor
void func(){
-a*5+fmyNumber(a,b);
}

void func(){
+5/!a - x&&!"constant string";
}

void func(){
-!a*(5+b) || faFunction(b*2, func());
}

void func(){
+(!b)/b-"as"&&"k";
}

void func(){
func()&&fanother(6, 2.8, b) || (fibo(7)/!fisAMalware());
}


void func(){
"this is a string"*4 - a/!(a-b);
}

//expresion -> expresion simple {= expresion simple | <relacion> expresion simple}
void func(){
-a*5+fmyNumber(a,b) = -a;
}

void func(){
+5/!a - x&&!"constant string" = func()&&fanother(6, 2.8, b) || (fibo(7)/!fisAMalware());
}

void func(){
-!a*(5+b) || faFunction(b*2, func())  == 7;
}

void func(){
+(!b)/b-"as"&&"k" <= 3421.5648;
}

void func(){
func()&&fanother(6, 2.8, b) || (fibo(7)/!fisAMalware()) != fparabolicNumber(x,y,z);
}


void func(){

b = b*8+factorial(4);

}

//proposicion compuesta -> { [lista de declaracion] [lista de proposiciones] }
void func(){
int a;
int a = 5;
float val[];
float values[3];
float v[] = {2.5};
float values[] = {2.5, 3.1, 7.8};
int index[2] = {};
int indexes[3] = {5,7};
int indexes[3] = {5,7,321};
func()&&fanother(6, 2.8, b) || (fibo(7)/!fisAMalware()) != fparabolicNumber(x,y,z);
b = b*8+factorial(4);
+(!b)/b-"as"&&"k" <= 3421.5648;
}

void func(){
int a;
int a = 5;
float val[];
float values[3];
float v[] = {2.5};
float values[] = {2.5, 3.1, 7.8};
int index[2] = {};
int indexes[3] = {5,7};
int indexes[3] = {5,7,321};
+(!b)/b-"as"&&"k" <= 3421.5648;
func()&&fanother(6, 2.8, b) || (fibo(7)/!fisAMalware()) != fparabolicNumber(x,y,z);
b = b*8+factorial(4);
}


void func(){
int a = 5;
int b = 2;
int c;

c=a+b;

fiDoACallHere(c, -a);

{
int a = b;
b = c+4;
func(2*a,3*b);
}
}

float func(){

int a = 5;
int b = 2;
int c;

c=a+b;

float z = fiDoACallHere(c, -a);

{
int a = b;
b = c+4;

func(2*a,3*b);
}

return z;
}

float func(){

int a = 5;
int b = 2;
int c;

c=a+b;

fiDoACallHere(c, -a);

{
int a = b;
b = c+4;

func(2*a,3*b);
}

return c;
}

void func() {
int i = 0;

while(i<10){
fexecutefunc();
i = i+1;
}
}

void func() {
int i = 0;

while(i<10) fexecutefunc(i);

return c;
}

void func() {
int a = 6, b = 7;
if(a<b) return 1;
}

void func() {
int a = 6, b = 7;
if(a<b) return 1 else 0;
}

void func() {
int a = 6, b = 7;
if(a<b){
a = !fisLogic(-1,+4) || func();
}
}

void func() {
int a = 6, b = 7;
if(a>=b){
b = !fisLogic(-1,+4) || func();
return b;
}
else return a;
}

void func() {
int a = 6, b = 7;
if(a>=b){
b = !fisLogic(-1,+4) || func();
return b;
}
else{
float v[] = {2.5};
b = b*8+factorial(4);
func()&&fanother(6, 2.8, b) || (fibo(7)/!fisAMalware()) != fparabolicNumber(x,y,z);
return a;
}
}

int func(){

int a = 5;
int b = 2;
int c;

c=a+b;

cin >> a >> b >> c;

return c;
}

int func(){
cout << 5 << 8+factorial(4);
}

int func(float a, float b){
    int i = 0;

    while(i<10){
        if(a+b < func1(a,b))
            return a;           
        else {
            a = 2*a;
            b = 2*b;
        }
        i=i+1;
    }

    return a+b;
}

int func(float a, float b){
    int i = 0;

    if(a < b)
        while(i < b)
            a = 2*b;
    else
        while (i < a)
            b = 2*a;
    
    return a+b;
}


int func(float a, float b){
    int i = 0;

    if(a < b){
        while(i < b){
            a = 2*b;
        }
    }
    else{
        while (i < a)
            b = 2*a;
    }
    return a+b;
}
