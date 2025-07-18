#include <stdio.h>
int return_value(int);

int main()
{
    int x;
    printf("Enter the index:");
    scanf("%d", &x);
    int value = return_value(x);
    printf("The value at index %d is %d\n", x, value);
}