#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11 * sizeof(char)); // Allocate memory for 10 characters + null terminator

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    int i;
    for (i = 0; i < 10 && (scanf("%c", &buf[i]) != EOF); ++i);

    buf[i] = '\0'; // Null-terminate the string

    printf("You entered: %s\n", buf);

    free(buf);
    return 0;
}