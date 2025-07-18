#include <stdio.h>
int main(void) {
    int argc;
    char *argv[2];
    if (argc != 2) {
        printf("Error");
        return 1;
    }
    input = argv[1];
    printf(input);
    input = trimwhitespace(input);
    printf(input);
    return 0;
}