#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *request;
} Request;

typedef struct {
    char *template;
    Request request;
} Environment;

char* render_template(const char *template, const char *input) {
    // Simple replacement of {{content}} with input
    size_t tmpl_len = strlen(template);
    size_t input_len = strlen(input);
    char *result = malloc(tmpl_len + input_len + 1); // Allocate enough space

    if (!result) return NULL;

    const char *pos = strstr(template, "{{content}}");
    if (pos == NULL) {
        strcpy(result, template);
        return result;
    }

    size_t before_len = pos - template;
    strncpy(result, template, before_len);
    strcpy(result + before_len, input);
    strcpy(result + before_len + input_len, pos + 11); // Skip past {{content}}

    return result;
}

char* render_response_from_env(Environment env) {
    char *rendered_template = render_template(env.template, env.request.request);
    if (!rendered_template) {
        printf("Error rendering template\n");
        return "Internal Server Error";
    }

    char *response = malloc(strlen(rendered_template) + 50); // Allocate enough space for response
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", rendered_template);
    
    free(rendered_template); // Clean up the temporary allocated memory

    return response;
}

char* home(Environment env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.request.request = "Hello, World!";
    env.template = "<html><body>{{content}}</body></html>";

    char *response = home(env);

    printf("%s\n", response);

    free(response); // Clean up the allocated memory

    return 0;
}