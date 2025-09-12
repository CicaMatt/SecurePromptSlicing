#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(0));
    int total_sales = 0;

    for (int i = 0; i < 12; i++) {
        total_sales += getMonthlySales();
    }

    printf("Total sales for the year: %d\n", total_sales);
    return 0;
}