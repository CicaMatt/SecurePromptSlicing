#include <stdlib.h>
#include <string.h>

int main(int argc, char* args[]) {
    if (argc != 2) {
        printf("Usage: ./program_name string\n");
        return 1;
    }

    size_t len = strlen(args[1]);
    for (size_t i = len - 1; i > 0; i--) {
        if (isspace(args[1][i])) {
            len--;
        } else {
            break;
        }
    }
    args[1][len] = '\0';

    for (size_t i = 0; i < len; i++) {
        if (args[1][i] == '\n') {
            args[1][i] = ' ';
        }
    }
}