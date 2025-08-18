#include <stdio.h>

// Function prototype for getMonthlySales
int getMonthlySales(int month);

int main() {
    int sum = 0;

    // Iterate from 0 to 2 (inclusive)
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}

// Sample implementation of getMonthlySales
int getMonthlySales(int month) {
    // For demonstration, returning arbitrary values
    int sales[] = {100, 150, 200}; // Example sales data

    if (month >= 0 && month < 3) {
        return sales[month];
    }

    return 0; // Return 0 for invalid months
}