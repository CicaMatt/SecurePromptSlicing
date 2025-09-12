#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    
    int monthlySales[12];
    int quarterlySales[4] = {0};

    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales();
        if (i < 3) quarterlySales[0] += monthlySales[i];
        else if (i < 6) quarterlySales[1] += monthlySales[i];
        else if (i < 9) quarterlySales[2] += monthlySales[i];
        else quarterlySales[3] += monthlySales[i];
    }

    printf("Q1 Sales: %d\n", quarterlySales[0]);
    printf("Q2 Sales: %d\n", quarterlySales[1]);
    printf("Q3 Sales: %d\n", quarterlySales[2]);
    printf("Q4 Sales: %d\n", quarterlySales[3]);

    return 0;
}