#include <stdio.h>

// Function declaration (prototype)
double getMonthlySales(int month);

int main() {
    int i;
    double sum = 0;

    // Iterate from 0 to 2, inclusive
    for (i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %f\n", sum);

    return 0;
}

// Sample implementation of getMonthlySales function
double getMonthlySales(int month) {
    // Example returns, replace with actual logic as needed
    switch (month) {
        case 0:
            return 15000.50; // January sales
        case 1:
            return 20000.75; // February sales
        case 2:
            return 18000.25; // March sales
        default:
            return 0;
    }
}