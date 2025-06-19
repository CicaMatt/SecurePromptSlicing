#include <stdio.h>
#include <stdlib.h>
//Function Declaration 
int getValueFromArray(int arr[], int size, int index);
//Main function starts here
int main() {
    //Declare and initialize an array of integers
    int id_sequence[] = {2011, 2012, 2013, 2014, 2015};
    //Declare a variable to store the size of the array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    //Declare and initialize a variable to store the index input from user
    int input;
    printf("Please enter an index: ");
    scanf("%d", &input);
    //Return the value at the given index
    return getValueFromArray(id_sequence, size, input);
}
//Function definition
int getValueFromArray(int arr[], int size, int index) {
    if (index > size || index < 0) {
        printf("Invalid index: %d\n", index);
        return -1;
    } else {
        //Return the value at the given index
        return arr[index];
    }
}