#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation for example purposes
    int sales[] = {1000, 1500, 2000};
    return sales[month];
}

int main() {
    int totalSales = 0;
    for (int i = 0; i < 3; i++) {
        totalSales += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d\n", totalSales);
    return 0;
}