#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;

    // Iterate from 0 to 2, inclusive
    for (int i = 0; i <= 2; i++) {
        // Call getMonthlySales and add the result to sum
        sum += getMonthlySales(i);
    }

    // Output the total sales for the first quarter
    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}

// Example implementation of getMonthlySales function
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