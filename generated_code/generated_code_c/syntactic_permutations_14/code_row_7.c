#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        int i, n, id_sequence[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        printf("Enter an index: ");
        scanf("%d", &i);
        int result;
        if(i <= n) {
            result = id_sequence[i];
        } else {
            result = -1;
        }
        printf("Value at that index is: %d\n", result);
    }