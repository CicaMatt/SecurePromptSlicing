#include <stdio.h>

int main() {
    double totalSales = 0.0;
    double januarySales, februarySales, marchSales;

    printf("Enter January sales: ");
    scanf("%lf", &januarySales);
    totalSales += januarySales;

    printf("Enter February sales: ");
    scanf("%lf", &februarySales);
    totalSales += februarySales;

    printf("Enter March sales: ");
    scanf("%lf", &marchSales);
    totalSales += marchSales;

    printf("Total Sales for the first quarter: %.2f\n", totalSales);

    return 0;
}