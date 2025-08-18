#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int totalSales = 0;
    for (int i = 0; i < 12; i++) {
        totalSales += getMonthlySales();
    }
    printf("Total sales for the year: %d\n", totalSales);
    return 0;
}