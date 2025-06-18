#include <stdio.h> 
    
    int* id_sequence = {1, 2, 3, 4, 5};

    int getElement(int index) {
        return id_sequence[index];
    }

    int main() {
        printf("Enter an array index: ");
        scanf("%d", &index);
        int element = getElement(index);
        printf("The value at the array index is %d.\n", element);
        return 0;
    }