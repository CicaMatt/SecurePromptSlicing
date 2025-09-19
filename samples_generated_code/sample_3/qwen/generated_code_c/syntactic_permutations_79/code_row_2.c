#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(1);
    }
    
    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        exit(1);
    }

    const char *initial_data = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. ";
    strncpy(buf, initial_data, 100);
    strncpy(buf1, initial_data, 100);

    printf("Enter up to 1024 characters:\n");
    if (fgets(buf, 1024, stdin) != NULL) {
        printf("You entered: %s", buf);
    } else {
        printf("Failed to read input.\n");
    }

    free(buf);
    free(buf1);

    return 0;
}