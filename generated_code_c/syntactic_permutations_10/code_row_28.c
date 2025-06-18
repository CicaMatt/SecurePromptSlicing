#include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    int getValueFromArray(const int32_t *arr, const uint64_t size, const uint64_t index) {
        if (index >= size || arr == NULL) {
            return 0;
        }
    
        return arr[index];
    }
    
    int main() {
        const int32_t id_sequence[] = {1, 2, 3, 4, 5};
        uint64_t index;
    
        scanf("%lu", &index);
    
        exit(getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int32_t), index));
    }