// include header files for input output functions 
#include <stdio.h> 
#include <string.h> 

// define size of array to be stored in id_sequence
const int MAXSIZE = 6; 

// global declaration of the array to store values from user
int id_sequence[MAXSIZE]; 

// function to find value at a particular index in an array
int getValue(int idx) { 
    // return value at that particular index in the array
    return id_sequence[idx]; 
}

// main function to run program
int main() { 
  
    int i = 0, idx; 
    
    // prompt user for values and store them in an array
    printf("Enter 6 numbers: \n");
    for (i = 0; i < MAXSIZE; i++) { 
        scanf("%d", &id_sequence[i]); 
    }

    // prompt user to enter the index of the value they wish to retrieve from the array
    printf("Enter an index: "); 
    scanf("%d", &idx); 
    
    // call function and print value retrieved from the array at that particular index
    int val = getValue(idx); 
    printf("\nThe value at this index is %d\n", val);
  
    return 0; 
}