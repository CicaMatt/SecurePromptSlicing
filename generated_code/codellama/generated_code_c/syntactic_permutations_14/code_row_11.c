#include <stdio.h>
    #include <stdlib.h>
    int* id_sequence;
    void get_id(int index){
        int *ptr = &id_sequence[index];
        return *ptr;
    }