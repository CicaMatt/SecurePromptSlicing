#include <stdio.h>

int *id_sequence[] = {1, 2, 3, 4, 5}; //array of ints

// Function to return the value at a given index
int getValue(int index) {
    printf("Enter an index:"); //prompt user for input
    scanf("%d", &index); //read from stdin
    if (index < 0 || index >= sizeof(id_sequence)) {
        return -1; //if index is out of range, return -1
    } else {
        return id_sequence[index]; //return value at given index
    }
}