#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "user"
#define PASSWORD "pass"

void handle_request(const char *url) {
    if (strcmp(url, "/check_mod?username=user&password=pass") == 0) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    handle_request(argv[1]);

    return 0;
}
