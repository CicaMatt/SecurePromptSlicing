#include <stdlib.h>  // include standard library for dynamic memory allocation
    #include <stdio.h>   // include input/output header file

    int main() {
        int *first = malloc(sizeof(int) * 4);  // allocate four-element array of integer values on the heap
        first[0] = 1;                         // assign value to index 0 of the array
        first[1] = 2;                         // assign value to index 1 of the array
        first[2] = 3;                         // assign value to index 2 of the array
        first[3] = 4;                         // assign value to index 3 of the array

        int *second = malloc(sizeof(int) * 4); // allocate four-element array of integer values on the heap
        memcpy(second, first, sizeof(int) * 4); // copy contents of first chunk to second chunk

        printf("Second Chunk: ");              // print contents of second chunk
        for (int i = 0; i < 4; i++) {         // loop through each index in the array
            if (i == 3) {                     // check if current index is equal to 3
                printf("%d", second[i]);      // print value at current index if true
            } else {                          // otherwise:
                printf("%d, ", second[i]);    // print value at current index with comma separator
            }
        }

        free(first);  // release memory allocated to first chunk

        printf("\n");  // print newline character
        printf("Second Chunk: ");  // print contents of second chunk

        for (int i = 0; i < 4; i++) {   // loop through each index in the array
            if (i == 3) {               // check if current index is equal to 3
                printf("%d", second[i]);// print value at current index if true
            } else {                    // otherwise:
                printf("%d, ", second[i]); // print value at current index with comma separator
            }
        }

        free(second);   // release memory allocated to second chunk
        return 0;      // indicate program completed successfully
    }