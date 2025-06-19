// 
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void fill_buffer(char* buffer, const unsigned int size) {
        memset(buffer, 'A', size);
    }
    
    char my_buffer[32];
    
    int main(void) {
        fill_buffer(my_buffer, 32);
        return 0;
    }