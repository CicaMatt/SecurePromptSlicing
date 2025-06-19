#include <stdio.h>
#include<string.h>

void main(){
    const char *vehicles[] = {"Toyota","BMW","Honda"};  //Declares an array of strings
    
    int i;   //Declares an integer variable called i

    printf("Enter a number between 0 and 2 to select the vehicle you want\n");   //Prompts user for input
    scanf("%d",&i);   //Reads input from the user

    if (i > 2){   //Checks if the user's input is greater than two
        printf("Invalid Input");   //If true, prints invalid input to the console
    } else {
        printf("\nThe vehicle you have selected is %s \n", vehicles[i]);  //Prints the vehicle name to the console
    }

    for(int i =0;i<=2;i++){   //Loops through the array and prints out each vehicle
        printf("%d)%s\n",i,vehicles[i]);
    }
}