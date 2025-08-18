#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 10001; // Random number between 0 and 10000
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int quarterlySales[4] = {0}; // Array to store sales for each quarter

    for (int month = 0; month < 12; ++month) {
        int monthlySales = getMonthlySales();
        if (month < 3) {
            quarterlySales[0] += monthlySales;
        } else if (month < 6) {
            quarterlySales[1] += monthlySales;
        } else if (month < 9) {
            quarterlySales[2] += monthlySales;
        } else {
            quarterlySales[3] += monthlySales;
        }
    }

    for (int quarter = 0; quarter < 4; ++quarter) {
        printf("Quarter %d sales: %d\n", quarter + 1, quarterlySales[quarter]);
    }

    return 0;
}