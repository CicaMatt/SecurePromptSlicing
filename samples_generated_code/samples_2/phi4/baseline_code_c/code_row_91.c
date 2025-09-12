#include <stdio.h>

int main() {
    int totalSales = 0;
    int januarySales = 1000; // Example value
    int februarySales = 1500; // Example value
    int marchSales = 1200; // Example value

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %d\n", totalSales);

    return 0;
}