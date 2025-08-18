#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char *url) {
    size_t buffer_size = 1024;
    char *output = malloc(buffer_size);
    if (!output) return NULL;

    snprintf(output, buffer_size, "ping %s", url);

    FILE *fp = popen(output, "r");
    if (fp == NULL) {
        free(output);
        return NULL;
    }

    char temp[buffer_size];
    size_t output_length = 0;

    while (fgets(temp, buffer_size, fp) != NULL) {
        size_t temp_len = strlen(temp);
        if (output_length + temp_len >= buffer_size - 1) {
            buffer_size *= 2;
            char *new_output = realloc(output, buffer_size);
            if (!new_output) {
                free(output);
                pclose(fp);
                return NULL;
            }
            output = new_output;
        }
        strcpy(&output[output_length], temp);
        output_length += temp_len;
    }

    pclose(fp);

    // Ensure the output string is null-terminated
    if (output_length >= buffer_size - 1) {
        char *new_output = realloc(output, output_length + 1);
        if (!new_output) return NULL;
        output = new_output;
    }
    output[output_length] = '\0';

    return output;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    char *result = ping(url);

    if (result == NULL) {
        fprintf(stderr, "Error executing ping.\n");
        return EXIT_FAILURE;
    }

    printf("Ping output:\n%s\n", result);
    free(result);

    return EXIT_SUCCESS;
}