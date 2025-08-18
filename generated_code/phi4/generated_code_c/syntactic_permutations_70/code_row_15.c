#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of the CGI environment variables.
#define MAX_ENV_VARS 128
extern char **environ;

typedef struct {
    const char *name;
    char *value;
} EnvVar;

EnvVar env_vars[MAX_ENV_VARS];

int get_env_var(const char *name) {
    for (int i = 0; environ[i]; ++i) {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=') {
            return 1;
        }
    }
    return 0;
}

char* get_env_value(const char *name) {
    for (int i = 0; environ[i]; ++i) {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=') {
            return strdup(environ[i] + strlen(name) + 1);
        }
    }
    return NULL;
}

void save_file(const char *filename, const char *content, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(content, sizeof(char), length, file);
        fclose(file);
    }
}

void upload_file() {
    char boundary[256];
    snprintf(boundary, sizeof(boundary), "%s", get_env_value("HTTP_CONTENT_TYPE"));
    printf("Content-type: text/html\n\n");
    
    FILE *input = fopen("php://stdin", "rb");
    if (input == NULL) return;

    // Read the HTTP request body into a buffer
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        const char *boundaryPtr = strstr(buffer, boundary);
        if (boundaryPtr) {
            // Process file content before this boundary
            save_file("uploads/uploaded_file", buffer, boundaryPtr - buffer);
            break;
        }
    }

    fclose(input);
}

int main() {
    upload_file();
    return 0;
}