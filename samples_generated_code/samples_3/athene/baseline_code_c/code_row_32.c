#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int quarterly_sales[4] = {0};
    
    for (int i = 0; i < 12; i++) {
        int sales = getMonthlySales();
        quarterly_sales[i / 3] += sales;
    }

    printf("Quarterly Sales:\n");
    for (int i = 0; i < 4; i++) {
        printf("Q%d: %d\n", i + 1, quarterly_sales[i]);
    }
    
    return 0;
}