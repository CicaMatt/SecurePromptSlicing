#include <stdio.h>
    #define BUFFER_SIZE 12
    int main()
    {
        char buffer[BUFFER_SIZE];
        for(int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = 'A';
        }
        return 0;
    }