#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy function implementation, returns a fixed value for demonstration
    return 1000 + (month * 100); // Example: 1000, 1100, 1200 for months 0, 1, 2
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}