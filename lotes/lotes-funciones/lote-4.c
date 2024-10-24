int a;

int myFunc(char a, char b, char c){
 return a*b*c;
}

void foo(){
 a = myFunc(foo(), a);
}
