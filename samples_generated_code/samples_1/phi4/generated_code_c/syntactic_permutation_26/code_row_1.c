#include <stdio.h>

// Function prototype declaration
double getMonthlySales(int month);

int main() {
    double sum = 0.0;
    int i;

    // Iterate from 0 to 2
    for (i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %.2f\n", sum);

    return 0;
}

// Example implementation of getMonthlySales function
double getMonthlySales(int month) {
    switch (month) {
        case 0:
            return 10000.50; // January sales
        case 1:
            return 15000.75; // February sales
        case 2:
            return 12000.25; // March sales
        default:
            return 0.0;
    }
}