#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    int getMonthlySales() {
        return rand() % 100000;
    }

    void main() {
        srand(time(NULL));

        float salesTotal = 0;
        for (int i = 1; i <= 12; i++) {
            salesTotal += getMonthlySales();

            if ((i % 3) == 0) {
                printf("Quarter %d: %.2f\n", i / 3, salesTotal);
            }
        }

        printf("\nYearly total: %.2f\n", salesTotal);
    }