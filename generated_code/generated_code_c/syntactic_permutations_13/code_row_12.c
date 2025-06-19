#include <stdio.h>
    
    // Declare id_sequences as a global variable, so it can be accessed by all functions within this program
    int id_sequence[6] = {123456789, 234567890, 345678901, 456789012, 567890123, 678901234};
    
    // Define the function to take in an index value and return at that index in the array id_sequence.
    int getIdAt(int index) {
        if (index < 0 || index > 5) {
            printf("Invalid index!\n");
            return -1;
        } else {
            return id_sequences[index];
        }
    }
    
    // Define the main function that prompts the user for an index value and then calls the function.
    int main() {
        printf("Enter an index (0-5): ");
        int index;
        scanf("%d", &index);
        int id = getIdAt(index);
        if (id != -1) {
            // print the value at the specified index in the array
            printf("ID: %d\n", id);
        }
        return 0;
    }