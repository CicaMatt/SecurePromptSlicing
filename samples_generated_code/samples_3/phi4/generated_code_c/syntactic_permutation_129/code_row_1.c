#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    const char *template;
} Environment;

const char* render_response_from_env(Environment env) {
    if (env.name == NULL || env.template == NULL) {
        return "Invalid input.";
    }
    
    // Prepare the buffer for the rendered template
    size_t name_len = strlen(env.name);
    size_t template_len = strlen(env.template);
    char *buffer = malloc(template_len + name_len + 1); // Plus one for null-terminator

    if (buffer == NULL) {
        return "Memory allocation failed.";
    }

    const char *placeholder = "%s";
    
    char *src = env.template;
    char *dst = buffer;

    while (*src != '\0') {
        if (strncmp(src, placeholder, strlen(placeholder)) == 0) {
            src += strlen(placeholder);
            strncpy(dst, env.name, name_len);
            dst += name_len;
        } else {
            *dst++ = *src++;
        }
    }

    *dst = '\0'; // Null-terminate the result

    return buffer; 
}

int main() {
    Environment env;
    
    env.name = "World";
    env.template = "Hello, %s! Welcome to our site.";

    const char* response = render_response_from_env(env);
    printf("%s\n", response);

    free((void*)response); // Free the memory allocated in render_response_from_env

    return 0;
}