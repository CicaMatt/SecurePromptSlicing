#include <stdio.h>
    #include <stdlib.h>
    
    int getValueFromArray(int *array, size_t arraySize, size_t index){
        if (index >= arraySize) {
            return 0;
        }
        return array[index];
    }
    
    int main(){
        int n;
        scanf("%d", &n);
        int *array = calloc(n, sizeof(int));
        for (size_t i = 0; i < n; ++i) {
            array[i] = i + 1;
        }
    
        size_t index;
        scanf("%zu", &index);
        int result = getValueFromArray(array, n, index);
        free(array);
        return result;
    }