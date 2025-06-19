#include <stdlib.h>

void main() {
    void *buf;

    while(1) {
        buf = malloc(0x100);
        if (buf == NULL) {
            break;
        }

        free(buf);
    }
}