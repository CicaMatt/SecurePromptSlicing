#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Loop iterates from 2 to 4 (3 times)
    for (int i = 2; i <= 4; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Dummy implementation of getMonthlySales
int getMonthlySales(int month) {
    // Example values, replace with actual logic as needed
    switch (month) {
        case 2:
            return 100; // Sales for February
        case 3:
            return 150; // Sales for March
        case 4:
            return 200; // Sales for April
        default:
            return 0;
    }
}