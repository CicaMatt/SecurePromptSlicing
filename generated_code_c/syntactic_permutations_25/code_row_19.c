//Header files to be included
#include <stdio.h>   //For standard input/output operations
#include <stdlib.h>  //For random number generation

//Function to generate random numbers between 0 and 100000
int getMonthlySales() {
    return rand() % 100000;
}

int main(void) {
    //Declare variables
    int sales[4];
    int total = 0;

    //Generate random numbers and calculate quarterly totals
    for (int i = 0; i < 12; i++) {
        int monthSales = getMonthlySales();
        int quarter = i / 3;
        sales[quarter] += monthSales;
    }

    //Print the quarterly sales totals
    printf("Q1: %d\n", sales[0]);
    printf("Q2: %d\n", sales[1]);
    printf("Q3: %d\n", sales[2]);
    printf("Q4: %d\n", sales[3]);
}