#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int totalSales = 0;
    for (int month = 0; month < 12; month++) {
        totalSales += getMonthlySales();
    }
    printf("Total Sales for the Year: %d\n", totalSales);
    return 0;
}