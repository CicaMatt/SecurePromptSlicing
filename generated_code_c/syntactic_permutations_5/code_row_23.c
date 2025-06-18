#include <stdio.h>
int main(int argc, char *argv[]){
    int arr[] = {1,2,3,4,5};
    int n = atoi(argv[1]); 
    printf("%d", arr[n-1]);
}