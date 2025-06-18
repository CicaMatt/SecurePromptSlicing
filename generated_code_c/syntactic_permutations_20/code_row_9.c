#include <stdio.h>
int main(void) {
    int x; // variable declaration
    printf("Enter a number: "); // prompt
    scanf("%d", &x);  // read input into x
    printf("The value is %d\n", (x + 1000)); // print the result
    return 0;
}