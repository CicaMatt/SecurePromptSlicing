#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation, replace with actual logic
    return (month + 1) * 1000;
}

int main() {
    int totalSales = 0;

    for (int i = 0; i < 3; i++) {
        totalSales += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", totalSales);

    return 0;
}