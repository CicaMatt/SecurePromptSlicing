#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation for demonstration purposes
    int sales[] = {100, 200, 150};
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