#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales(int month) {
    return rand() % 1000 + 1; // Random number between 1 and 1000
}

void calculateAndPrintQuarterlySales() {
    int monthlySales[12];
    int quarterlySales[4] = {0};

    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales(i + 1);
        quarterlySales[i / 3] += monthlySales[i];
    }

    printf("Quarterly Sales:\n");
    for (int i = 0; i < 4; ++i) {
        printf("Q%d: %d\n", i + 1, quarterlySales[i]);
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    calculateAndPrintQuarterlySales();
    return 0;
}