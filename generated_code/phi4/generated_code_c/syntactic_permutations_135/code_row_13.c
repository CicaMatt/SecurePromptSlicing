#include <stdio.h>
#include <string.h>

// Function declarations
int check_mod(const char *input, const char *correct);

int main(void) {
    // Example usage of check_mod()
    char userInput[100];
    char correctValue[] = "expected_value";

    printf("Enter a value: ");
    if (fgets(userInput, sizeof(userInput), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(userInput);
        if (len > 0 && userInput[len - 1] == '\n') {
            userInput[len - 1] = '\0';
        }

        if (check_mod(userInput, correctValue)) {
            printf("Correct!\n");
        } else {
            printf("Incorrect.\n");
        }
    }

    return 0;
}

// Function definition
int check_mod(const char *input, const char *correct) {
    return strcmp(input, correct) == 0;
}