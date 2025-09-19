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

char* render_template(const char *template, const Request *request) {
    // Simulating template rendering by concatenating request to template
    size_t len = strlen(template) + strlen(request->request) + 1;
    char *rendered = malloc(len);
    if (rendered == NULL) {
        return NULL;
    }
    snprintf(rendered, len, "%s%s", template, request->request);
    return rendered;
}

char* render_response_from_env(const Environment *env) {
    char *rendered_template = render_template(env->template, &env->request);
    if (rendered_template == NULL) {
        return "Error: Template rendering failed";
    }
    // Simulating a response
    size_t len = strlen(rendered_template) + 1;
    char *response = malloc(len);
    if (response == NULL) {
        free(rendered_template);
        return "Error: Memory allocation failed";
    }
    snprintf(response, len, "%s", rendered_template);
    free(rendered_template);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .template = "<html><body>Hello, ",
        .request = {.request = "World!"}
    };

    char *response = home(&env);
    printf("%s</body></html>\n", response);

    free(response);
    return 0;
}