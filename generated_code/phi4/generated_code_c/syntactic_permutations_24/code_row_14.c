#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int num1 = rand() % (991) + 10;
    int num2 = rand() % (991) + 10;

    printf("First number: %d\n", num1);
    printf("Second number: %d\n", num2);

    if (num1 > num2) {
        printf("The first number is greater.\n");
    } else if (num1 < num2) {
        printf("The second number is greater.\n");
    } else {
        printf("Both numbers are equal.\n");
    }

    return 0;
}