#include <stdio.h>

// Function prototype declaration
float getMonthlySales(int month);

int main() {
    int i;
    float sum = 0.0;

    // Iterate from 0 to 2 (inclusive)
    for (i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %.2f\n", sum);

    return 0;
}

// Dummy implementation of getMonthlySales
float getMonthlySales(int month) {
    switch (month) {
        case 0:
            return 15000.50; // Example sales for January
        case 1:
            return 20000.75; // Example sales for February
        case 2:
            return 25000.25; // Example sales for March
        default:
            return 0.0;
    }
}