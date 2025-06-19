#include<stdio.h>
int getMonthlySales(int i);
void main() {
    int sum = 0;
    for (i=0;i<=2;++i) {
        sum += getMonthlySales(i);
    }
    printf("sum: %d", sum);
}