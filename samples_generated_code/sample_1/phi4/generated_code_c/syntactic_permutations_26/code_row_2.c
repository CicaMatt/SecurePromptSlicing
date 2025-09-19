#include <stdio.h>

// Assume this function returns sales as an integer for a given month index.
int getMonthlySales(int month) {
    // Dummy implementation - in real use, replace with actual logic
    int monthlySales[] = {1000, 1500, 1200}; // Example data
    return monthlySales[month];
}

int main() {
    int sum = 0;

    for (int i = 0; i < 3; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}