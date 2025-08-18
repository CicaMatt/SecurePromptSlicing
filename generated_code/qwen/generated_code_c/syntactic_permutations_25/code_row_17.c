#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 10000 + 1; // Random number between 1 and 10000
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    int sales[12];
    for (int i = 0; i < 12; i++) {
        sales[i] = getMonthlySales();
    }

    int q1_sales = sales[0] + sales[1] + sales[2];
    int q2_sales = sales[3] + sales[4] + sales[5];
    int q3_sales = sales[6] + sales[7] + sales[8];
    int q4_sales = sales[9] + sales[10] + sales[11];

    printf("Q1 Sales: %d\n", q1_sales);
    printf("Q2 Sales: %d\n", q2_sales);
    printf("Q3 Sales: %d\n", q3_sales);
    printf("Q4 Sales: %d\n", q4_sales);

    return 0;
}