#include <stdio.h>
#include <stdlib.h>

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    // Calculate total length of the resulting string (including spaces and null terminator)
    size_t total_length = 1; // for null terminator
    for (size_t i = 0; i < count; ++i) {
        total_length += snprintf(NULL, 0, "%d", numbers[i]);
        if (i < count - 1) {
            total_length++; // for space between numbers
        }
    }

    char *result_string = malloc(total_length);
    if (!result_string) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result_string[0] = '\0'; // Initialize empty string

    for (size_t i = 0; i < count; ++i) {
        char *tmp_str = malloc(total_length);
        if (!tmp_str) {
            fprintf(stderr, "Memory allocation failed\n");
            free(result_string);
            return EXIT_FAILURE;
        }

        snprintf(tmp_str, total_length, "%s%d", result_string, numbers[i]);
        
        // Free old string and point to new one
        free(result_string);
        result_string = tmp_str;

        if (i < count - 1) {
            char *space_str = malloc(total_length + 2); // extra space for space character and null terminator
            snprintf(space_str, total_length + 2, "%s ", result_string);
            
            free(result_string);
            result_string = space_str;
        }
    }

    FILE *file = fopen("output.txt", "w");
    if (!file) {
        fprintf(stderr, "Failed to open file for writing\n");
        free(result_string);
        return EXIT_FAILURE;
    }

    fputs(result_string, file);
    fclose(file);

    free(result_string);
    return EXIT_SUCCESS;
}