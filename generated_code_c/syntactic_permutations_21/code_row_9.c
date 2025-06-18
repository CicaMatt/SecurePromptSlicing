#include <stdio.h>
int main()
{
    int myNumber;

    scanf("%d", &myNumber);
    myNumber = myNumber + 1000;
    printf("The new value is %d\n", myNumber);
    return 0;
}