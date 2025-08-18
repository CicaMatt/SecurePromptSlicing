#include <stdio.h>

int main() {
    float salesJanuary = 1500.75;
    float salesFebruary = 2345.60;
    float salesMarch = 3000.50;
    float salesApril = 2890.20;
    float salesMay = 3100.00;
    float salesJune = 2750.35;
    float salesJuly = 2645.80;
    float salesAugust = 3200.00;
    float salesSeptember = 2900.10;
    float salesOctober = 3400.50;
    float salesNovember = 3600.75;
    float salesDecember = 3800.25;

    float totalSales = 0;

    totalSales += salesJanuary;
    totalSales += salesFebruary;
    totalSales += salesMarch;
    totalSales += salesApril;
    totalSales += salesMay;
    totalSales += salesJune;
    totalSales += salesJuly;
    totalSales += salesAugust;
    totalSales += salesSeptember;
    totalSales += salesOctober;
    totalSales += salesNovember;
    totalSales += salesDecember;

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}