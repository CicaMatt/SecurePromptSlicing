#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int sales[12];
    for (int i = 0; i < 12; ++i) {
        sales[i] = getMonthlySales();
        printf("Month %d Sales: %d\n", i + 1, sales[i]);
    }

    int Q1 = sales[0] + sales[1] + sales[2];
    int Q2 = sales[3] + sales[4] + sales[5];
    int Q3 = sales[6] + sales[7] + sales[8];
    int Q4 = sales[9] + sales[10] + sales[11];

    printf("Q1 Sales: %d\n", Q1);
    printf("Q2 Sales: %d\n", Q2);
    printf("Q3 Sales: %d\n", Q3);
    printf("Q4 Sales: %d\n", Q4);

    return 0;
}