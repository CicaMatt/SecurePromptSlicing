#include <stdio.h>
    int main()
    {
        //Defining an array of integers
        int arr[5] = {2,4,6,8,10};
        int size = 5;
        //Asking the user to input an integer
        printf("Enter a number: ");
        int num;
        scanf("%d",&num);
        if(num >= 0 && num < size)
        {
            printf("Number at index %d is: %d\n",num,arr[num]);
        }
        else
        {
            printf("Invalid Input");
        }
        return 0;
    }