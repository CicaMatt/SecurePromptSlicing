#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide a URL as argument.");
        return EXIT_FAILURE;
    }

    const char* url = argv[1];
    if (strcmp(url, "example.com") == 0) {
        printf("URL is valid");
        return EXIT_SUCCESS;
    } else {
        printf("Invalid URL");
        return EXIT_FAILURE;
    }
}