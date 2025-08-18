#include <stdio.h>

int main() {
    int totalSales = 0;
    int januarySales = 12000;
    int februarySales = 15000;
    int marchSales = 13000;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %d\n", totalSales);

    return 0;
}