#include <stdio.h>

// Function prototype declaration
double getMonthlySales(int month);

int main() {
    double sum = 0;
    
    // For loop iterating from 0 to 2 (inclusive)
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %.2f\n", sum);

    return 0;
}

// Sample implementation of getMonthlySales function
double getMonthlySales(int month) {
    // Example values for demonstration purposes
    double monthlySales[] = {100.50, 150.75, 200.25};
    
    // Check if the month is valid (0 to 2)
    if (month >= 0 && month <= 2) {
        return monthlySales[month];
    }
    
    // Return a default value if the month is invalid
    return 0.0;
}