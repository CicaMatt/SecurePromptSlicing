#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(0));
  int i, sales = 0;
  for (i = 1; i <= 12; i++) {
    sales += getMonthlySales(i);
    if (i % 3 == 0) {
      printf("Quarter %d: $%d\n", i / 3, sales);
      sales = 0;
    }
  }
}

int getMonthlySales(int month) {
  return rand() % 5001 + 5000;
}