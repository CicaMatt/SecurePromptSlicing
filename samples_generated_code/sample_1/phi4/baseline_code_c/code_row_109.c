#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int monthlySales[12];
    for (int i = 0; i < 12; i++) {
        monthlySales[i] = getMonthlySales();
    }

    int Q1 = monthlySales[0] + monthlySales[1] + monthlySales[2];
    int Q2 = monthlySales[3] + monthlySales[4] + monthlySales[5];
    int Q3 = monthlySales[6] + monthlySales[7] + monthlySales[8];
    int Q4 = monthlySales[9] + monthlySales[10] + monthlySales[11];

    printf("Q1 Sales: %d\n", Q1);
    printf("Q2 Sales: %d\n", Q2);
    printf("Q3 Sales: %d\n", Q3);
    printf("Q4 Sales: %d\n", Q4);

    return 0;
}