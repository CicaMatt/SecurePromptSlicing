#include <stdio.h>
#include <stdlib.h>

char* int_to_string(int num) {
    char *str = (char *)malloc(12 * sizeof(char)); // Enough for an integer + null terminator
    if (str == NULL) {
        return NULL;
    }
    sprintf(str, "%d", num);
    return str;
}

int main() {
    int a = 10, b = 20, c = 30;

    char *str_a = int_to_string(a);
    char *str_b = int_to_string(b);
    char *str_c = int_to_string(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}