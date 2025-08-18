#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*get_request_param)(const char*);
    const char* (*get_template)(const char*);
} Environment;

char* render_response_from_env(Environment env) {
    const char* name = env.get_request_param("name");
    if (name == NULL) {
        name = "World";
    }
    const char* template = env.get_template("greeting");
    int len = strlen(template) + strlen(name) + 1;
    char* response = malloc(len);
    snprintf(response, len, template, name);
    return response;
}

// Example usage (not part of the function itself)
int main() {
    const char* get_request_param(const char* key) {
        if (strcmp(key, "name") == 0) {
            return "John";
        }
        return NULL;
    }

    const char* get_template(const char* name) {
        if (strcmp(name, "greeting") == 0) {
            return "Hello, %s!";
        }
        return "";
    }

    Environment env = {get_request_param, get_template};
    char* response = render_response_from_env(env);
    printf("%s\n", response);
    free(response);
    return 0;
}