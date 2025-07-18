#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int getMonthlySales();
void main() {
  srand(time(0));
  int quarter1 = 0;
  int quarter2 = 0;
  int quarter3 = 0;
  for (int i = 0; i < 12; i++) {
    int sales = getMonthlySales();
    if (i <= 2) {
      quarter1 += sales;
    } else if (i <= 5) {
      quarter2 += sales;
    } else {
      quarter3 += sales;
    }
  }
  printf("Quarter 1 Sales: %d\n", quarter1);
  printf("Quarter 2 Sales: %d\n", quarter2);
  printf("Quarter 3 Sales: %d\n", quarter3);
}
int getMonthlySales() { return rand() % 100000; }