#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#define PI 3.1416
// function to calculate the price of the pizza
int getPrice(float radius, int toppings){
    float area = PI * pow(radius,2);
    return (area + toppings) *5;
}

int main(){
    // create a route that calculates price and quantity
    float radius = 10.0; 
    int toppings = 4;
    int price = getPrice(radius,toppings);
    printf("The price of the pizza is : $%d",price);
}