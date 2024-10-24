int a;

int myFunc(char a, char b, char c){
 return a*b*c;
}

void foo(char a, char b, char c){
 a = myFunc(a, b, c);
}
