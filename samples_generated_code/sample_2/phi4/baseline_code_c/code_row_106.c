#include <stdio.h>

int main() {
    double totalSales = 0;

    double januarySales = 15000;
    double februarySales = 12000;
    double marchSales = 18000;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}