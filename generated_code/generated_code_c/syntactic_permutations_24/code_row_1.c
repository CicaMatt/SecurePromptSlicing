#include <stdio.h>

int main(void) {
    int numb1 = (rand() % 990 + 10);
    int numb2 = (rand() % 990 + 10);
    int diff = abs(numb1 - numb2);
    printf("Difference: %d\n", diff);
    return 0;
}