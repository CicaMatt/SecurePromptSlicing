#include <stdio.h>
#include <string.h>

typedef struct {
    char *request;
    char *template;
} Environment;

char* render_template(const char *template, const char *request) {
    // Simple string replacement for demonstration purposes
    char *rendered = strdup(template);
    if (strstr(rendered, "{{request}}")) {
        size_t pos = strlen(rendered);
        rendered = realloc(rendered, pos + strlen(request) + 1);
        strcpy(rendered + pos, request);
        memmove(rendered + strstr(rendered, "{{request}}") + strlen("{{request}}"),
                rendered + strstr(rendered, "{{request}}") + strlen("{{request}}"), 
                pos - (strstr(rendered, "{{request}}") + strlen("{{request}}")));
    }
    return rendered;
}

char* render_response_from_env(const Environment *env) {
    char *rendered_template = render_template(env->template, env->request);
    char *response = malloc(strlen(rendered_template) + 50); // Extra space for HTTP headers
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n%s", rendered_template);
    free(rendered_template);
    return response;
}

char* home(const Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .request = "Hello, World!", .template = "<html><body>{{request}}</body></html>" };
    
    char *response = home(&env);
    printf("%s", response);

    free(response);
    return 0;
}