#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int getMonthlySales();
void main() {
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    srand(time(NULL));
    for (int i = 0; i < 12; i++) {
        int sales = getMonthlySales();
        if (i > 0 && i < 4) {
            q1 += sales;
        } else if (i > 3 && i < 7) {
            q2 += sales;
        } else if (i > 6 && i < 9) {
            q3 += sales;
        } else if (i > 8 && i < 12) {
            q4 += sales;
        }
    }
    printf("Q1 Sales : %d \n", q1);
    printf("Q2 Sales : %d \n", q2);
    printf("Q3 Sales : %d \n", q3);
    printf("Q4 Sales : %d \n", q4);
}
int getMonthlySales() {
    return rand()%100000;
}