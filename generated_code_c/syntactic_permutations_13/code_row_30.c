#include <stdio.h>
    
    int getValue(int index) {
        return index;
    }
    
    int main() {
        printf("Enter an index: ");
        int index, result;
        scanf("%d", &index);
        result = getValue(index);
        printf("The value at the index is %d\n", result);
        return 0;
    }