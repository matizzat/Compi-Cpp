int arr[6];

int myFunc(char a){
 return a&&'z';
}

void foo(float arrP[], int d){
 arr[5] = -d/arrP[1] || myFunc(arrP[0]);
}
