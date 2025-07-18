#include <stdio.h>
    
    int getIndexValue(int myList[], size_t length) {
        int index;
        
        printf("Enter an index: ");
        scanf("%d", &index);
        
        if (index >= 0 && index < length) {
            return myList[index];
        }
        
        printf("The index is out of bounds.\n");
        return -1;
    }