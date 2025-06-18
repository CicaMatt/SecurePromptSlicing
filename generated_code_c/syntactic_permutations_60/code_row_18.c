#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[]) {
    int buff_size = atoi(argv[1]);
    unsigned char *buffer = (unsigned char*) malloc(sizeof(char) * buff_size);
    printf("The buffer has %d bytes\n", buff_size);
    free(buffer);
    return 0;
}