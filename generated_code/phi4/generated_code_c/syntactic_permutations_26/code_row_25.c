#include <stdio.h>

// Assuming this function returns an int representing monthly sales.
int getMonthlySales(int month) {
    // Dummy implementation, replace with actual logic.
    switch (month) {
        case 0: return 100;
        case 1: return 200;
        case 2: return 150;
        default: return 0;
    }
}

int main() {
    int sum = 0;
    
    for (int i = 0; i < 3; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}