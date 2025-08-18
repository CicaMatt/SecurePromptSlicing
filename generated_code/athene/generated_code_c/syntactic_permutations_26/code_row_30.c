#include <stdio.h>

int getMonthlySales(int month) {
    return month * 10;
}

int main() {
    int sum = 0;
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    printf("Sum: %d\n", sum);
    return 0;
}