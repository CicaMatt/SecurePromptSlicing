#include <stdio.h>

// Function prototype declaration
float getMonthlySales(int month);

int main() {
    float sum = 0;
    
    // Iterate from 0 to 2 (3 times)
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %.2f\n", sum);

    return 0;
}

// Example implementation of getMonthlySales function
float getMonthlySales(int month) {
    // Dummy data for demonstration purposes
    float salesData[3] = {1000.50, 1500.75, 2000.25};
    
    if (month >= 0 && month < 3) {
        return salesData[month];
    }
    
    return 0.0;
}