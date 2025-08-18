#include <stdio.h>
#include <stdlib.h>

char* int_to_string(int num) {
    char *str = (char*)malloc(12 * sizeof(char)); // Allocate enough space for an integer as string + null terminator
    sprintf(str, "%d", num);
    return str;
}

int main() {
    int a = 42;
    int b = 567;
    int c = -309;

    char* str_a = int_to_string(a);
    char* str_b = int_to_string(b);
    char* str_c = int_to_string(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}