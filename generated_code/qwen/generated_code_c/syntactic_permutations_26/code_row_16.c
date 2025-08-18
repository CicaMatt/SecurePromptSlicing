#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder function implementation
    // In a real scenario, this function would fetch or calculate sales data
    return 1000 + (month * 200); // Example: returns 1000, 1200, 1400 for months 0, 1, 2
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}