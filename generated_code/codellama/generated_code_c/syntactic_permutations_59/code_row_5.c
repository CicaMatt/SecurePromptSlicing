#include <stdint.h>
#define BUFFER_SIZE 1024 // or whatever value you want

void foo() {
    char buffer[BUFFER_SIZE];
    for (uint32_t i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 'A';
    }
}