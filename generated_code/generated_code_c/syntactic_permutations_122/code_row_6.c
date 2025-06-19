#include <stdlib.h>
#include <string.h>

int main() {
    void *ptr1 = malloc(10);
    if (ptr1 == NULL) {
        return 1;
    }

    void *ptr2 = malloc(10);
    if (ptr2 == NULL) {
        free(ptr1);
        return 1;
    }

    memcpy(ptr2, ptr1, 10);
    free(ptr1);
    free(ptr2);
}