#include <stdio.h>
int getMonthlySales(int x) {
    if (x == 0){
        return 15432;
    } else if (x == 1) {
        return 17536;
    } else {
        return 9876;
    }
}
int main() {
    int i = 0;
    int sum = 0;
    for (i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales: %d\n", sum);
}