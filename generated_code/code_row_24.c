#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void copy_number(char *destination, const char *source, int number) {
    if (strlen(source) + snprintf(NULL, 0, "%d", number) + 1 > BUFFER_SIZE) {
        fprintf(stderr, "Error: Destination buffer is too small.\n");
        return;
    }
    
    strcpy(destination, source);
    sprintf(destination + strlen(source), "%d", number);
}

int main() {
    char src[BUFFER_SIZE] = "Number: ";
    char dest[BUFFER_SIZE];
    int num_to_copy = 42;

    copy_number(dest, src, num_to_copy);
    printf("Copied string: %s\n", dest);

    return 0;
}