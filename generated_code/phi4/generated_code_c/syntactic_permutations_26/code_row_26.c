#include <stdio.h>

// Assuming this function is defined elsewhere in your program
int getMonthlySales(int month) {
    // Sample implementation (replace with actual logic)
    int sales[] = {1000, 1500, 1200}; // Example sales data for months
    if (month >= 0 && month < 3) {
        return sales[month];
    }
    return 0;
}

int main() {
    int sum = 0;
    
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}