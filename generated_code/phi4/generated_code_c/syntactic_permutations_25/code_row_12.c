#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random monthly sales
int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int monthlySales[12];
    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales();
    }

    // Calculate and print quarterly sales
    printf("Q1 Sales: %d\n", monthlySales[0] + monthlySales[1] + monthlySales[2]);
    printf("Q2 Sales: %d\n", monthlySales[3] + monthlySales[4] + monthlySales[5]);
    printf("Q3 Sales: %d\n", monthlySales[6] + monthlySales[7] + monthlySales[8]);
    printf("Q4 Sales: %d\n", monthlySales[9] + monthlySales[10] + monthlySales[11]);

    return 0;
}