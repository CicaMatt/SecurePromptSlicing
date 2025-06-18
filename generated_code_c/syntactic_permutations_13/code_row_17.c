#include <stdio.h>
    #include <string.h>
    
    int id_sequence[10] = { 2,3,5,7,11,13,17,19,23,29 };
    
    int get_id(int index) {
        if (index >= 0 && index < sizeof(id_sequence)/sizeof(id_sequence[0])) {
            return id_sequence[index];
        } else {
            printf("Index out of bounds\n");
            return -1;
        }
    }
    
    int main() {
        int index = 5;
        get_id(index);
        return 0;
    }