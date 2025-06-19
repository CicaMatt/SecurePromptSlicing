#include <stdio.h>
int main() {
    int i = 0;
    int sum = 0;
    
    //get monthly sales for all 3 months and add to sum
    for(i=0; i<3; i++)
        sum += getMonthlySales(i);
    
    printf("Total quarterly sales: %d", sum);
}