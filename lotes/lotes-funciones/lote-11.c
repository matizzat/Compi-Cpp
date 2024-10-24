int a;

int f1(){
 return 5;
}

char f2(){
 return 'c';
}

float f3(){
 return 2.7;
}

int f4(int arr[]){
 a = arr[0];
}



void f5(int arr[]){
 a = arr[0];
}



void f6(int arr[]){
 return a = arr[0];
}



int f7(int arr[]){
 if(arr[0]>34){
  return arr[1];
 }
}



int f8(int arr[]){
 if(arr[0]>34){
  return arr[1];
 }
 else
 {
  return 0;
 }
}



int f9(void x, char b, char c){
 if(x&&b||c){
  a = x+a;
 }
 else
 {
  return c;
 }
}



int f9(char x, char b, char c){
 if(x&&b||c){
  a = x+a;
 }
 else
  while (!b<a)
  {
    return c;
  }
}



void main(){
 int vector[5] = {5,4,3,2,1};
 a = a + f1(vector);
 return a;
}
