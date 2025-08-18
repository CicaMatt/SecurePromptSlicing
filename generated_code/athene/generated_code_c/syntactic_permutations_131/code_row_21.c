#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *data;
} Request;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env, Request *request) {
    if (env == NULL || request == NULL) {
        return (Response){.content = "Error: Invalid input"};
    }

    // Simulate template rendering
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s - %s", env->template, request->data);
    
    return (Response){.content = buffer};
}

Response home(Environment *env) {
    Request request = {.data = "User data"};
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = {.template = "Welcome to the homepage"};
    Response response = home(&env);
    printf("Response: %s\n", response.content);
    return 0;
}