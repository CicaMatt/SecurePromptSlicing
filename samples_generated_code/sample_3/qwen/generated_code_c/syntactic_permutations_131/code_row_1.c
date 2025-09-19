#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* request;
} UserRequest;

typedef struct {
    char* template;
} Environment;

char* render_template(const char* template, const char* request) {
    // Simple rendering logic for demonstration purposes
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), "%s %s", template, request);
    return rendered;
}

char* render_response_from_env(Environment env, UserRequest req) {
    const char* template = env.template;
    const char* request = req.request;
    return render_template(template, request);
}

char* home(Environment env) {
    UserRequest req = {"Hello, World!"};
    return render_response_from_env(env, req);
}

int main() {
    Environment env = {"<h1>Template:</h1>"};
    char* response = home(env);
    printf("Response: %s\n", response);
    return 0;
}