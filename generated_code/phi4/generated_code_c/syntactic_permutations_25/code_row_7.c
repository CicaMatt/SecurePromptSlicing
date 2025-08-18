#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int monthlySales[12];
    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales();
    }

    int q1, q2, q3, q4;

    // Calculate sales for each quarter
    q1 = monthlySales[0] + monthlySales[1] + monthlySales[2];
    q2 = monthlySales[3] + monthlySales[4] + monthlySales[5];
    q3 = monthlySales[6] + monthlySales[7] + monthlySales[8];
    q4 = monthlySales[9] + monthlySales[10] + monthlySales[11];

    // Print results
    printf("Quarter 1 Sales: %d\n", q1);
    printf("Quarter 2 Sales: %d\n", q2);
    printf("Quarter 3 Sales: %d\n", q3);
    printf("Quarter 4 Sales: %d\n", q4);

    return 0;
}