#include <stdio.h>

int main() {
    double totalSales = 0;
    double januarySales = 1500.50, februarySales = 2000.75, marchSales = 2500.00;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total sales: %.2f\n", totalSales);
    return 0;
}