#include <stdio.h>
#include <stdlib.h>

void read_characters(void) {
    char *buffer = (char *)malloc(1024);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    printf("Enter 10 characters: ");
    int i;
    for (i = 0; i < 10 && getchar() != '\n'; ++i) {
        buffer[i] = getchar();
    }
    
    buffer[i] = '\0';
    printf("You entered: %s\n", buffer);

    free(buffer);
}

int main(void) {
    read_characters();
    return 0;
}