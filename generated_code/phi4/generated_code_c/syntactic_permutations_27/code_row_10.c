#include <stdio.h>

int main() {
    double totalSales = 0;
    double januarySales = 10000, februarySales = 12000, marchSales = 15000;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}