#include <stdio.h>

    int main() {
        int i, sum = 0;
        for (i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }