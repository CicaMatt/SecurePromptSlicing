#include <stdio.h>

// Function prototype declaration
double getMonthlySales(int month);

int main() {
    double sum = 0;

    // Iterate from 0 to 2 (inclusive)
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %.2f\n", sum);

    return 0;
}

// Function definition
double getMonthlySales(int month) {
    double monthlySales;

    // Simulating getting different sales values based on month index
    switch (month) {
        case 0:
            monthlySales = 1500.50; // January Sales
            break;
        case 1:
            monthlySales = 1200.75; // February Sales
            break;
        case 2:
            monthlySales = 1800.30; // March Sales
            break;
        default:
            monthlySales = 0.0;
    }

    return monthlySales;
}