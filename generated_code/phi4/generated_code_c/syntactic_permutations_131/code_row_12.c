#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_template(const Environment *env) {
    return env->template;
}

char* render_template_with_name(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate memory for the result
    char *result = malloc(template_len + name_len + 1); // +1 for null terminator

    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Copy template and insert name where needed
    const char *p = template;
    char *q = result;

    while (*p != '\0') {
        if (strncmp(p, "{name}", 6) == 0) { // Find placeholder for the name
            strcpy(q, name);
            q += name_len;
            p += 6; // Skip past the placeholder
        } else {
            *q++ = *p++;
        }
    }

    *q = '\0'; // Null-terminate the result

    return result;
}

char* render_response_from_env(const Environment *env) {
    const char *template = get_template(env);
    char *rendered = render_template_with_name(template, env->name);

    return rendered;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    // Example usage
    Environment env = {
        .name = "Alice",
        .template = "Hello, {name}!"
    };

    char *response = home(&env);

    printf("%s\n", response);

    free(response); // Free the memory allocated for the response

    return 0;
}