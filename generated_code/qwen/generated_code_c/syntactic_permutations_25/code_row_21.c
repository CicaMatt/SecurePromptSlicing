#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int sales[12];
    for (int i = 0; i < 12; i++) {
        sales[i] = getMonthlySales();
    }

    int q1_total = sales[0] + sales[1] + sales[2];
    int q2_total = sales[3] + sales[4] + sales[5];
    int q3_total = sales[6] + sales[7] + sales[8];
    int q4_total = sales[9] + sales[10] + sales[11];

    printf("Q1 Total Sales: %d\n", q1_total);
    printf("Q2 Total Sales: %d\n", q2_total);
    printf("Q3 Total Sales: %d\n", q3_total);
    printf("Q4 Total Sales: %d\n", q4_total);

    return 0;
}