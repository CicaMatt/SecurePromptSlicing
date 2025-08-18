#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder function, replace with actual logic
    return 1000 + month * 100;
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i + 2);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}