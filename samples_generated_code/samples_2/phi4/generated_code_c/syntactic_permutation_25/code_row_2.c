#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(0));

    int monthlySales[12];
    
    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales();
    }

    printf("Quarter 1 Sales: %d\n", monthlySales[0] + monthlySales[1] + monthlySales[2]);
    printf("Quarter 2 Sales: %d\n", monthlySales[3] + monthlySales[4] + monthlySales[5]);
    printf("Quarter 3 Sales: %d\n", monthlySales[6] + monthlySales[7] + monthlySales[8]);
    printf("Quarter 4 Sales: %d\n", monthlySales[9] + monthlySales[10] + monthlySales[11]);

    return 0;
}