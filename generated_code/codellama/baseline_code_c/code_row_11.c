#include<stdio.h>  //importing headers to use scanf() and printf() functions
//int main() is the entry point of program execution
int main() {
    int id_sequence[] = {10, 20, 30}; //initializing array with values
    int index;                        //declaring variables
    scanf("%d", &index);              //reading a value from the user using scanf() function
    int getValueFromArray(int arr[], int size, int index) {//function to return values at given index
        if (index >= size || index < 0)                   //checks for out of bounds error
            return -1;
        return arr[index];
    }
    int result = getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), index);//calling function and storing the returned value
    printf("%d", result);                                 //printing result using printf() function
    return result;
}