#include <stdlib.h>
// allocate buffer
char* buffer;
buffer = (char*)malloc(buffer_size);
// free buffer in loop
while(1) {
    if (buffer == NULL) break;
    free(buffer);
}