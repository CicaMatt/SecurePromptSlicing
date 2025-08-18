#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_input(char *buf) {
    int i;
    for (i = 0; i < 10 && ((buf[i] = getchar()) != '\n' && buf[i] != EOF); ++i);
    buf[i] = '\0';
}

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    read_input(buf);
    
    printf("You entered: %s\n", buf);
    
    free(buf);
    return 0;
}