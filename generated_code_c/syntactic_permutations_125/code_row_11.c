#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please enter a string as an argument");
        return 1;
    }

    const char* inputString = argv[1];
    int inputLength = strlen(inputString);
    int trimmedLength = 0;

    while (trimmedLength < inputLength && inputString[trimmedLength] != ' ') {
        trimmedLength += 1;
    }

    char* outputString = malloc(sizeof(char) * trimmedLength + 1);
    strncpy(outputString, inputString, trimmedLength);
    outputString[trimmedLength] = '\0';

    printf("%s", outputString);
    free(outputString);

    return 0;
}