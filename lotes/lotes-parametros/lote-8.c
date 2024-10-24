int global = 0;

void foo(char a, int b, void &c[]){
 global = a + b + c;
}
