#include <stdio.h>

int main() {
    double totalSales = 0;
    double januarySales, februarySales, marchSales;

    printf("Enter January Sales: ");
    scanf("%lf", &januarySales);
    totalSales += januarySales;

    printf("Enter February Sales: ");
    scanf("%lf", &februarySales);
    totalSales += februarySales;

    printf("Enter March Sales: ");
    scanf("%lf", &marchSales);
    totalSales += marchSales;

    printf("Total Sales for the first quarter: %.2f\n", totalSales);

    return 0;
}