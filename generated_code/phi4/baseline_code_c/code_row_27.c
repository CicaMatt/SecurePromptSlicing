#include <stdio.h>

int main() {
    int totalSales = 0;
    int januarySales = 1000, februarySales = 1200, marchSales = 900;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %d\n", totalSales);

    return 0;
}