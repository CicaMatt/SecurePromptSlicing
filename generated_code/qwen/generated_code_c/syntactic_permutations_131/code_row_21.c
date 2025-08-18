#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *request;
} UserRequest;

typedef struct {
    char *template;
} Environment;

char* render_template(const char *template, const char *request) {
    // Simple template rendering logic (for demonstration purposes)
    static char response[256];
    snprintf(response, sizeof(response), "%s %s", template, request);
    return response;
}

char* render_response_from_env(Environment *env) {
    UserRequest user_request = {"Hello from User"};
    const char *rendered_template = render_template(env->template, user_request.request);
    return strdup(rendered_template);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"Welcome to the Home Page: %s"};
    char *response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}