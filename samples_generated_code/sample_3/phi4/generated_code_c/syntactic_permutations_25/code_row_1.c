#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001; // Random number from 0 to 100000
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int monthlySales[12];
    int quarterlySales[4] = {0};

    for (int i = 0; i < 12; i++) {
        monthlySales[i] = getMonthlySales();
    }

    for (int i = 0; i < 3; i++) {
        quarterlySales[i] = monthlySales[i] + monthlySales[i+1] + monthlySales[i+2];
    }

    printf("Quarterly Sales:\n");
    for (int i = 0; i < 3; i++) {
        printf("Q%d: %d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}