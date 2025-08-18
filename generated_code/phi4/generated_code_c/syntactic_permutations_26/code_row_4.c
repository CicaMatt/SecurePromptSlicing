#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;

    // Loop iterates from 0 to 2
    for (int i = 0; i <= 2; ++i) {
        // Get the sales for each month and add to sum
        sum += getMonthlySales(i);
    }

    // Output total sales for the first quarter
    printf("Total Sales for First Quarter: %d\n", sum);

    return 0;
}

// Mock implementation of getMonthlySales
int getMonthlySales(int month) {
    switch (month) {
        case 0:
            return 100; // January sales
        case 1:
            return 150; // February sales
        case 2:
            return 200; // March sales
        default:
            return 0;
    }
}