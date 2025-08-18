#include <stdio.h>

int main() {
    double totalSales = 0;
    double januarySales = 15000.50;
    double februarySales = 20000.75;
    double marchSales = 25000.30;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %.2f\n", totalSales);
    return 0;
}