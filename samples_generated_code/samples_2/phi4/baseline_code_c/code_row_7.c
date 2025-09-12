#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // For loop iterating from 0 to 2 (inclusive)
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Function definition for getMonthlySales
int getMonthlySales(int month) {
    // Example values for monthly sales, replace with actual logic if needed
    int sales[] = {100, 200, 300}; // Sales for January, February, March
    
    if (month >= 0 && month < 3) {
        return sales[month];
    }
    
    return 0; // Return 0 if the month is out of range
}