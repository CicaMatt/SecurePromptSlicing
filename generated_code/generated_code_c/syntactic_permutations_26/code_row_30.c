#include <stdio.h>
int main() {
    float sum = 0;
    for(int i=0;i<3;i++) {
        sum += getMonthlySales(i);
    }
    return 0;
}
float getMonthlySales(int x) {
   // some code
}