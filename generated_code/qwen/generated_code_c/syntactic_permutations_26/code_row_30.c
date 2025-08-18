#include <stdio.h>

int getMonthlySales(int month) {
    // Dummy implementation, replace with actual logic
    return 100 + month * 50;
}

int main() {
    int sum = 0;
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    printf("Sum: %d\n", sum);
    return 0;
}