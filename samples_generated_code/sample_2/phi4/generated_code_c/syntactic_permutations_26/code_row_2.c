#include <stdio.h>

// Function prototype
double getMonthlySales(int month);

int main() {
    double sum = 0.0;
    int i;

    // Loop from 0 to 2
    for (i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %.2f\n", sum);

    return 0;
}

// Example implementation of getMonthlySales function
double getMonthlySales(int month) {
    // Mock data representing monthly sales
    double salesData[] = {1000.50, 1500.75, 1200.25};

    if (month >= 0 && month < 3) {
        return salesData[month];
    } else {
        return 0.0; // Return zero for invalid months
    }
}