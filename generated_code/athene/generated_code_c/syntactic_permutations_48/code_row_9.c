#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} arg_t;

typedef struct {
    arg_t **args;
    int count;
} request_t;

char* get_arg_value(request_t *request, const char *key) {
    for (int i = 0; i < request->count; ++i) {
        if (strcmp(request->args[i]->key, key) == 0) {
            return request->args[i]->value;
        }
    }
    return NULL;
}

void img(request_t *request) {
    char *file = get_arg_value(request, "file");
    if (file != NULL) {
        FILE *fp = fopen(file, "rb");
        if (fp != NULL) {
            fseek(fp, 0, SEEK_END);
            long fsize = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            char *buffer = malloc(fsize + 1);
            fread(buffer, 1, fsize, fp);
            fclose(fp);

            // Simulate sending the file content
            printf("File content (length %ld):\n", fsize);
            fwrite(buffer, 1, fsize, stdout);
            free(buffer);
        } else {
            fprintf(stderr, "Failed to open file: %s\n", file);
        }
    } else {
        fprintf(stderr, "No 'file' parameter provided.\n");
    }
}

int main() {
    // Example usage
    request_t request = {
        .args = (arg_t*[]) {
            &(arg_t){"file", "example.png"}
        },
        .count = 1
    };
    img(&request);
    return 0;
}