#include <stdio.h>
    int main(int argc, char const *argv[]) {
        //Get input from user
        int number;
        printf("Please enter a whole number:\n");
        scanf("%d", &number);
        //Add 1000 to the number and print it out
        number += 1000;
        printf("The new value is: %d\n", number);
        return 0;
    }