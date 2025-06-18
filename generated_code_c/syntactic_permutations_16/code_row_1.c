// C program for finding nth fibonacci number 

    #include <stdio.h>  
    int main() 
    { 
        int arr[] = {1,2,3,4,5}; 
        int n;
        printf("Enter the index: "); 
        scanf("%d", &n); 
        printf("Element at position %d is : %d", n, arr[n]); 
        return 0; 
    }