#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t template_len = 0;
    while (template[template_len] != '\0') template_len++;
    
    size_t name_len = 0;
    while (name[name_len] != '\0') name_len++;
    
    // Calculate buffer size for the resulting string
    size_t result_size = template_len + name_len + 2; // extra space for replacement and null-terminator
    char *result = malloc(result_size);
    
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    const char *src = template;
    char *dst = result;
    
    while (*src != '\0') {
        if (*(src + 1) == '{' && *(src + 2) == '}' && *(src + 3) == '\0') {
            src += 4; // Skip past the placeholder
            strcpy(dst, name);
            dst += name_len;
        } else {
            *dst++ = *src++;
        }
    }
    
    *dst = '\0';
    return result;
}

char* render_response_from_env(const Environment *env) {
    const char *name_param = "ExampleName"; // Simulated request parameter
    char *rendered_template = render_template(env->template, name_param);
    return rendered_template;
}

void home() {
    Environment env = { .name = "home", .template = "Hello, {!}!" };
    char *response = render_response_from_env(&env);
    
    printf("Response: %s\n", response);
    free(response); // Free the allocated memory for the rendered template
}

int main() {
    home();
    return 0;
}