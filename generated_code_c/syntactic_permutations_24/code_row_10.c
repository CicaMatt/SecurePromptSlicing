#include <stdio.h>
#include <stdlib.h>
int main() {
    int num1 = 10 + rand() % (1000 - 10);
    int num2 = 10 + rand() % (1000 - 10);
    printf("%d\n", num1 - num2);
    return 0;
}