#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales(void) {
    return rand() % 100000;
}

int main(void) {
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 12; i++) {
        switch (i / 3 + 1) {
            case 1:
                q1 += getMonthlySales();
                break;
            case 2:
                q2 += getMonthlySales();
                break;
            case 3:
                q3 += getMonthlySales();
                break;
            case 4:
                q4 += getMonthlySales();
                break;
        }
    }

    printf("Q1 sales: %d\n", q1);
    printf("Q2 sales: %d\n", q2);
    printf("Q3 sales: %d\n", q3);
    printf("Q4 sales: %d\n", q4);
}