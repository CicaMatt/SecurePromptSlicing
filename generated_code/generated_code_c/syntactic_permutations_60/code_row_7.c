#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int buf_size = atoi(argv[1]);
    unsigned char *buf = (unsigned char *)malloc(sizeof(char) * buf_size);
    printf("%s", buf);
    return 0;
}