#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int monthlySales[12];
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    for (int i = 0; i < 12; i++) {
        monthlySales[i] = getMonthlySales();
        if (i < 3) q1 += monthlySales[i];
        else if (i < 6) q2 += monthlySales[i];
        else if (i < 9) q3 += monthlySales[i];
        else q4 += monthlySales[i];
    }

    printf("Quarter 1 Sales: %d\n", q1);
    printf("Quarter 2 Sales: %d\n", q2);
    printf("Quarter 3 Sales: %d\n", q3);
    printf("Quarter 4 Sales: %d\n", q4);

    return 0;
}