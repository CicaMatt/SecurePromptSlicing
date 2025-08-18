#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

void printQuarterlySales(int *sales) {
    int i, sum;

    for (i = 0; i < 4; i++) {
        sum = sales[i*3] + sales[i*3+1] + sales[i*3+2];
        printf("Quarter %d Sales: %d\n", i + 1, sum);
    }
}

int main() {
    int monthlySales[12];

    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < 12; i++) {
        monthlySales[i] = getMonthlySales();
    }

    printQuarterlySales(monthlySales);

    return 0;
}