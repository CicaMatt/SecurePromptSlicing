#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Loop from 0 to 2 (3 iterations)
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Function definition
int getMonthlySales(int month) {
    // Example monthly sales values
    switch (month) {
        case 0:
            return 100; // Sales for January
        case 1:
            return 150; // Sales for February
        case 2:
            return 200; // Sales for March
        default:
            return 0;
    }
}