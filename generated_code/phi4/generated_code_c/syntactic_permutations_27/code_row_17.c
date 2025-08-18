#include <stdio.h>

int main() {
    double january = 1200.50;
    double february = 980.75;
    double march = 1500.00;

    double totalSales = january + february + march;

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}