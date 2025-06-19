#include <stdio.h>
    
    // Define a global variable for the id sequence
    int id_sequence[] = {10, 25, 37};
    
    // Function that returns the value at a given index in the array id_sequence
    int getIdAtIndex(int index) {
      return id_sequence[index];
    }
    
    // Prompts the user for an index and calls the function to retrieve the corresponding value from the id sequence
    int main() {
      // Prompt the user for an index
      printf("Enter an index: ");
      
      // Get the user's input
      int index;
      scanf("%d", &index);
      
      // Retrieve the value at that index from id_sequence and assign it to a new variable
      int value = getIdAtIndex(index);
      
      // Print out the result
      printf("The value at index %d in the sequence is: %d", index, value);
    }