#include <stdio.h>

int calculateSales(int i) {
    // This function should contain logic to calculate sales based on the input i.
    // For demonstration purposes, let's assume it returns a fixed value or some simple calculation.
    return i * 100; // Example: sales are $100 for each iteration
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += calculateSales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}