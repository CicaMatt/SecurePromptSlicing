/* Write your code here */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales();
void printQuarterlySales(int sales1, int sales2, int sales3, int sales4);

int main(){
    srand(time(0));

    int quarter1 = 0;
    int quarter2 = 0;
    int quarter3 = 0;
    int quarter4 = 0;

    for (int i = 0; i < 12; i++){
        int sales = getMonthlySales();
        if (i <= 2){
            quarter1 += sales;
        }
        else if (i >= 3 && i <= 5) {
            quarter2 += sales;
        }
        else if (i >= 6 && i <= 8) {
            quarter3 += sales;
        }
        else {
            quarter4 += sales;
        }
    }

    printQuarterlySales(quarter1, quarter2, quarter3, quarter4);
}

int getMonthlySales(){
    int sales = rand() % 100000;
    return sales;
}
void printQuarterlySales(int quarter1, int quarter2, int quarter3, int quarter4){
    printf("Quarter 1: %d\n", quarter1);
    printf("Quarter 2: %d\n", quarter2);
    printf("Quarter 3: %d\n", quarter3);
    printf("Quarter 4: %d\n", quarter4);
}