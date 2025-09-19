#include <stdio.h>
#include <stdlib.h>

char* convert_to_string(int num) {
    char* result = (char*)malloc(12 * sizeof(char)); // Enough space for integer string representation including sign and null terminator
    if (result == NULL) {
        return NULL;  // Memory allocation failed
    }
    sprintf(result, "%d", num);
    return result;
}

int main() {
    int a = 10;
    int b = 20;
    int c = 30;

    char* str_a = convert_to_string(a);
    char* str_b = convert_to_string(b);
    char* str_c = convert_to_string(c);

    if (str_a != NULL && str_b != NULL && str_c != NULL) {
        printf("String A: %s\n", str_a);
        printf("String B: %s\n", str_b);
        printf("String C: %s\n", str_c);

        free(str_a);
        free(str_b);
        free(str_c);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}