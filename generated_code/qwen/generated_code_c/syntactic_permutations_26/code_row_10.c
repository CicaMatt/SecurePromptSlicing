#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation for demonstration purposes
    return month * 100;
}

int main() {
    int sum = 0;
    int i;

    for (i = 2; i <= 4; i++) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}