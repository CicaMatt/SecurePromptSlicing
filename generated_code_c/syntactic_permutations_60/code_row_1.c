#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <buffer size>\n", argv[0]);
        return -1;
    }
    
    int buffer_size = atoi(argv[1]);
    unsigned char *buf = malloc(buffer_size);

    for (int i = 0; i < buffer_size; i++) {
        buf[i] = i % 256;
    }

    for (int i = 0; i < buffer_size; i++) {
        printf("%d: 0x%02x\n", i, buf[i]);
    }
    
    free(buf);
    
}