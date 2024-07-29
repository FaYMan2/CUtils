#include<stdio.h>


int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a > b ? b : a;
}

int arrMin(char* arr,int n,size_t size){
    int m = *(char*)arr;
    for(int i =0;i<n;i++){
        char* pos = arr + i * size;
        m = min(m,(int)*pos);
    }
    return m;
}

int arrMax(char* arr,int n,size_t size){
    int m = *(char*)arr;
    for(int i =0;i<n;i++){
        char* pos = arr + i * size;
        m = max(m,(int)*pos);
    }
    return m;
}

int main(){
    int a = 1;
    int b = 2;
    int arr[] = {1,2,3,-1};
    int n = 4;
    printf("%d\t",arrMin((void*)arr,n,sizeof(arr[0])));
    printf("%d",arrMax((void*)arr,n,sizeof(arr[0])));
    return 0;
}