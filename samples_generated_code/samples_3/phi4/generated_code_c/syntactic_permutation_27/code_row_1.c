#include <stdio.h>

int main() {
    int totalSales = 0;
    int januarySales = 10000;
    int februarySales = 15000;
    int marchSales = 20000;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %d\n", totalSales);

    return 0;
}