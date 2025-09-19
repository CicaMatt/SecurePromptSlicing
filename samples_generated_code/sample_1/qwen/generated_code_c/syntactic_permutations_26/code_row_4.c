#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder function, replace with actual implementation
    return (month + 1) * 100; // Example: returns 100, 200, 300 for months 0, 1, 2
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}