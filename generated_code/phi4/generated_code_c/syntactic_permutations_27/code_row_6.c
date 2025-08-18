#include <stdio.h>

int main() {
    double totalSales = 0.0;
    double januarySales = 15000.75;
    double februarySales = 20000.50;
    double marchSales = 25000.25;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}