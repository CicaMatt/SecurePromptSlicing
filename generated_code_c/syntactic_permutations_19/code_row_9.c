// A simple C program that reads a number from user input
#include <stdio.h>
int main(){
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);
    printf("%d + 1000 = %d\n", x, (x+1000));
    return 0;
}