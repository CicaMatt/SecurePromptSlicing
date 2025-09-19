#include <stdio.h>

int main() {
    float totalSales = 0;
    float januarySales = 10000.50f;
    float februarySales = 15000.75f;
    float marchSales = 20000.25f;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}