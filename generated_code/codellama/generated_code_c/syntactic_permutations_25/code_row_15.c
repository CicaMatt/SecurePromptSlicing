#include <stdio.h>
    #include <stdlib.h>

    int getMonthlySales(void) {
      return rand() % 100000;
    }

    int main() {
        for (int i = 0; i < 4; ++i) {
            int sales_total = 0;
            printf("Quarter #%d: ", i + 1);
            for (int j = 0; j < 3; ++j) {
                sales_total += getMonthlySales();
            }
            printf("%d\n", sales_total);
        }
    }