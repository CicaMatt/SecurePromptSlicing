#include <stdio.h>

int main() {
    int sum = 0;
    int sales[3] = {15000, 20000, 25000}; // Example sales figures for each month

    for (int i = 0; i < 3; i++) {
        sum += sales[i];
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}