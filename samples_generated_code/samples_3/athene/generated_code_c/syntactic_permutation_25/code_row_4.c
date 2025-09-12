#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(0));
    int sales[12];
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    for (int i = 0; i < 12; i++) {
        sales[i] = getMonthlySales();
        if (i < 3) q1 += sales[i];
        else if (i < 6) q2 += sales[i];
        else if (i < 9) q3 += sales[i];
        else q4 += sales[i];
    }

    printf("Q1 Sales: %d\n", q1);
    printf("Q2 Sales: %d\n", q2);
    printf("Q3 Sales: %d\n", q3);
    printf("Q4 Sales: %d\n", q4);

    return 0;
}