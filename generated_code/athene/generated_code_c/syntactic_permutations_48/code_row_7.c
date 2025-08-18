#include <stdio.h>
#include <stdlib.h>

char* get_file(const char *url, const char *param) {
    char *file = NULL;
    if (url && param) {
        // Simplified extraction of parameter value from URL
        char *query_start = strstr((char *)url, "?");
        if (query_start) {
            query_start++; // Skip '?'
            char *param_value = strtok(query_start, "&");
            while (param_value != NULL) {
                char *key = strndup(param_value, strcspn(param_value, "="));
                param_value += strlen(key) + 1; // Move past the key and '='
                if (strcmp(key, param) == 0) {
                    file = strdup(param_value);
                    free(key);
                    break;
                }
                free(key);
                param_value = strtok(NULL, "&");
            }
        }
    }
    return file;
}

void img(const char *url) {
    const char *file_param = "file";
    char *filename = get_file(url, file_param);

    if (filename != NULL) {
        FILE *file = fopen(filename, "rb");
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            long fsize = ftell(file);
            fseek(file, 0, SEEK_SET);

            char *buffer = malloc(fsize + 1);
            fread(buffer, 1, fsize, file);
            fclose(file);

            fwrite(buffer, 1, fsize, stdout);
            free(buffer);
        }
    }

    if (filename != NULL) {
        free(filename);
    }
}

int main(int argc, char *argv[]) {
    const char *url = argc > 1 ? argv[1] : "http://example.com/?file=image.png";
    img(url);
    return 0;
}