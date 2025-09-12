#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int sales[12];
    int quarters[4] = {0};

    for (int i = 0; i < 12; ++i) {
        sales[i] = getMonthlySales();
        if (i < 3) quarters[0] += sales[i];
        else if (i < 6) quarters[1] += sales[i];
        else if (i < 9) quarters[2] += sales[i];
        else quarters[3] += sales[i];
    }

    for (int i = 0; i < 4; ++i) {
        printf("Quarter %d: %d\n", i + 1, quarters[i]);
    }

    return 0;
}