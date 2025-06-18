#include <stdio.h>
    int main(void)
    {
        int arr[10] = {1,2,3,4,5,6,7,8,9};
        printf("Enter the index value : ");
        scanf("%d", &x);
        if (arr[x] != 0)
        {
            printf("Value at index %d is %d", x, arr[x]);
        }
        else 
        {
            printf("Index %d does not exist", x);
        }
    }