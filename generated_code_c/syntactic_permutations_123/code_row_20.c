#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // The argument must be a string
        char* input = argv[0];
        int length = strlen(input);
        for (int i = 0; i < length; i++) {
            // Trim the string
        }
        for (int i = 0; i < length; i++) {
            // Trim the newlines
        }
        input[length] = '\0'; // Null terminate the string
    }
}