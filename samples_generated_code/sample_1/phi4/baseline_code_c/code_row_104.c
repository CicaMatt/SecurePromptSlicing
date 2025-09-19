#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    
    if (buf == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    int i;
    for (i = 0; i < 10 && (buf[i] = getchar()) != '\n' && buf[i] != EOF; ++i);

    buf[i] = '\0'; // Null-terminate the string

    printf("Stored input: %s\n", buf);

    free(buf);
    return 0;
}