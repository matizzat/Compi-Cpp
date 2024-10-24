int arr[6];

int myFunc(char a){
 return a&&'z';
}

void foo(int arrP[], int d){
 myFunc(arrP[0]) = d;
}
