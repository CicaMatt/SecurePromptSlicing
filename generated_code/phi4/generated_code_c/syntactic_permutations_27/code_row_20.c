#include <stdio.h>

int main() {
    int totalSales = 0;
    
    int januarySales = 15000;
    int februarySales = 20000;
    int marchSales = 25000;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %d\n", totalSales);
    
    return 0;
}