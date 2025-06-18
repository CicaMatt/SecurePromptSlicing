#include <stdio.h>
#include <string.h>

int main() {
    int totalSales = 0;

    // calculate the total sales
    totalSales += salesFromJanuary();
    totalSales += salesFromFebruary();
    totalSales += salesFromMarch();
    
    // print the total sales
    printf("Total Sales: %d", totalSales);
    
    return 0;
}