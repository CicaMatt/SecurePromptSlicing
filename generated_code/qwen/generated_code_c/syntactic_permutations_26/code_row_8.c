#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder function, replace with actual implementation
    return 1000 + month * 200; // Example: returns 1000, 1200, 1400 for months 0, 1, 2
}

int main() {
    int sum = 0;
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}