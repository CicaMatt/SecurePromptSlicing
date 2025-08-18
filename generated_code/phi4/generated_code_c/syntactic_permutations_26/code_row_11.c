#include <stdio.h>

// Function declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;

    // For loop iterating from 2 to 4 (inclusive)
    for (int i = 2; i <= 4; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}

// Function definition
int getMonthlySales(int month) {
    // Example implementation, replace with actual logic as needed
    switch (month) {
        case 2:
            return 100; // Sales value for February
        case 3:
            return 150; // Sales value for March
        case 4:
            return 200; // Sales value for April
        default:
            return 0;
    }
}