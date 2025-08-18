#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int num1 = (rand() % 991) + 10;
    int num2 = (rand() % 991) + 10;
    int result = num1 * num2;
    printf("Result: %d\n", result);
    return 0;
}