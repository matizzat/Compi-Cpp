int arr[6];

int myFunc(char a[]){
 return a[0]&&'z';
}

void foo(char arrP[], int d){
 d = arrP[1] = arr[1] = myFunc(arrP);
}
