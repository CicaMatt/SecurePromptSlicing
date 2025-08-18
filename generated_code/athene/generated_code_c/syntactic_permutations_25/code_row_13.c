#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    for (int i = 0; i < 12; i++) {
        int sales = getMonthlySales();
        if (i < 3) {
            q1 += sales;
        } else if (i < 6) {
            q2 += sales;
        } else if (i < 9) {
            q3 += sales;
        } else {
            q4 += sales;
        }
    }

    printf("Q1 Sales: %d\n", q1);
    printf("Q2 Sales: %d\n", q2);
    printf("Q3 Sales: %d\n", q3);
    printf("Q4 Sales: %d\n", q4);

    return 0;
}