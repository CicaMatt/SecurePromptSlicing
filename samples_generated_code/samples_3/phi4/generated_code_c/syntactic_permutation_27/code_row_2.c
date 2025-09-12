#include <stdio.h>

int main() {
    double totalSales = 0.0;

    double januarySales = 50000.0;
    double februarySales = 60000.0;
    double marchSales = 70000.0;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}