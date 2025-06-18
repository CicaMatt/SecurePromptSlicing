#include <stdio.h>
    int main(int argc, char* argv[]){
       int arr[6] = {10, 20, 30, 40, 50, 60};
       int index = atoi(argv[1]); //convert to integer
       printf("%d",arr[index]);
       return 0;
    }