#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
  return rand() % 100000;
}

void printQuarterlySales(int first, int second, int third) {
  printf("First Quarter Sales: $%d\n", first);
  printf("Second Quarter Sales: $%d\n", second);
  printf("Third Quarter Sales: $%d\n", third);
}

int main() {
    srand(time(0));
    int sales;
    for (int i = 1; i <= 12; i++) {
        if (i % 3 == 1) {
            sales += getMonthlySales();
        } else if (i % 3 == 2) {
            printQuarterlySales(sales);
            sales = getMonthlySales();
        } else {
            sales += getMonthlySales();
        }
    }
    printQuarterlySales(sales, sales);
    return 0;
}