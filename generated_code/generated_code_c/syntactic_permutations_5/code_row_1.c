#include <stdio.h> 
    int main(int argc, char* argv[]) { 
        if (argc > 1) { 
            int i = atoi(argv[1]);  
            int arr[] = {10,20,30,40,50}; 
            printf("%d\n", arr[i - 1]); 
        }
        return 0; 
    }