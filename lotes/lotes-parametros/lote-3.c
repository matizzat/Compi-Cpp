int global = 0;

void foo(char a, int b, float c){
 global = -5+a;
 {
  global = a+b+c;
  {
   global = -a-b*c;
  }
 }
}
