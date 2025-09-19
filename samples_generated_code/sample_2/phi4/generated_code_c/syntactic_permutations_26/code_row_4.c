#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // For loop iterating from 0 to 2
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Example implementation of getMonthlySales function
int getMonthlySales(int month) {
    // Dummy data representing monthly sales
    int monthly_sales[] = {100, 150, 200};
    
    if (month >= 0 && month < 3) {
        return monthly_sales[month];
    }
    return 0;  // Return 0 for invalid month index
}