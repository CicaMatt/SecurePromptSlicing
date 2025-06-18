#include <stdio.h>
    #define ARRAY_LEN 1024;
    int main (void)
    {
        char arr[ARRAY_LEN];
        int input, value;
        scanf("%d",&input);
        if(input > ARRAY_LEN){
            printf("Error: %d is not a valid index in the array.\n", input);
            return 1;
        } else {
            value = arr[input];
        }
        printf("%d\n",value);
        return 0;
    }