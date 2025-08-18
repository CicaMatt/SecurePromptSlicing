#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Loop from 0 to 2, inclusive
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales: %d\n", sum);
    return 0;
}

// Dummy implementation of getMonthlySales
int getMonthlySales(int month) {
    // Example values for demonstration purposes
    int monthly_sales[] = {100, 150, 200};
    if (month >= 0 && month < 3) {
        return monthly_sales[month];
    } else {
        return 0; // Return zero for invalid months
    }
}