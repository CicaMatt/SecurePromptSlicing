#include <stdlib.h>
int main() {
    void *ptr = malloc(10);
    void *ptr2 = malloc(10);
    memcpy(ptr, ptr2, 10);
    free(ptr);
    free(ptr2);
}