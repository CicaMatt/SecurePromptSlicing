#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Iterate from 0 to 2 (inclusive)
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Sample implementation of getMonthlySales
int getMonthlySales(int month) {
    // Assuming some static values for demonstration purposes
    int monthlySales[3] = {100, 150, 200};
    if (month >= 0 && month < 3) {
        return monthlySales[month];
    }
    return 0;
}