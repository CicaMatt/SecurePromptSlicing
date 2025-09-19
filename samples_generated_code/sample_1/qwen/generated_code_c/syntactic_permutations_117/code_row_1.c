#include <stdio.h>
#include <stdlib.h>

char* int_to_str(int num) {
    char* buffer = (char*)malloc(12); // Enough for -2^31 to 2^31-1, plus null terminator
    if (buffer != NULL) {
        sprintf(buffer, "%d", num);
    }
    return buffer;
}

int main() {
    int a = 42;
    int b = -7;
    int c = 1024;

    char* str_a = int_to_str(a);
    char* str_b = int_to_str(b);
    char* str_c = int_to_str(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}