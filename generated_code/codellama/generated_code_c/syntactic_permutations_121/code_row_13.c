//include required header files
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr1,*arr2;  //declaring two arrays of integer type
    arr1 = (int*)malloc(5*sizeof(int));//allocating memory to first array of size 5 integers
    for(int i=0;i<5;i++){
        arr1[i]=i+2;
    }  //initializing the elements in the first array
    printf("The elements in the first array are:\n");
    for(int i=0;i<5;i++){
        printf("%d\t",arr1[i]);
    }
    arr2 = (int*)malloc(10*sizeof(int));//allocating memory to second array of size 10 integers
    for(int i=0;i<10;i++){
        if(i <5){
            arr2[i]=arr1[i];
        }
        else{
            arr2[i]=i-4;
        }
    }  //initializing the elements in the second array by copying the first array and then initializing the remaining with other values
    printf("\nThe contents of second array are:\n");
    for(int i=0;i<10;i++){
        printf("%d\t",arr2[i]);
    }
    free(arr1); //freeing the memory allocated to first array
    arr1 = NULL;
    printf("\nMemory freed from first array\n");
    printf("The contents of second array are:\n");
    for(int i=0;i<10;i++){
        printf("%d\t",arr2[i]);
    }
    free(arr2);  //freeing the memory allocated to second array
    arr2 = NULL;
    return 0;
}