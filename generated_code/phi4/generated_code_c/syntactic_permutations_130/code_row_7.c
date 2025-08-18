#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate enough memory for the new string
    char *rendered = malloc((template_len + name_len + 1) * sizeof(char));
    
    if (rendered == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Replace placeholder with the actual name value
    const char *pos = strstr(template, "%name%");
    if (pos != NULL) {
        size_t pos_len = pos - template;
        memcpy(rendered, template, pos_len);
        strcpy(rendered + pos_len, name);
        strcpy(rendered + pos_len + name_len, pos + 6); // '%name%' has a length of 6
    } else {
        strcpy(rendered, template);
    }
    
    return rendered;
}

char* render_response_from_env(Request *req, Environment *env) {
    char *rendered_template = render_template(env->template, req->name);
    return rendered_template;
}

char* home(Environment *env) {
    Request req;
    req.name = "John Doe"; // Example name

    char *response = render_response_from_env(&req, env);
    return response;
}

int main() {
    Environment env;
    env.template = "Hello, %name%! Welcome to our site.";

    char *response = home(&env);
    printf("%s\n", response);

    free(response); // Free allocated memory
    return 0;
}