#include <stdio.h>

int main() {
    int totalSales = 0;
    int januarySales = 15000, februarySales = 22000, marchSales = 13000;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %d\n", totalSales);

    return 0;
}