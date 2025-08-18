#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *template;
} Response;

Response* create_response(const char *template) {
    Response *response = (Response*)malloc(sizeof(Response));
    response->template = template;
    return response;
}

const char* get_request_name() {
    static const char default_name[] = "World";
    // Simulate getting the name from a request
    return getenv("USER_NAME") ? getenv("USER_NAME") : default_name;
}

const char* get_template(Environment *env) {
    if (env && env->name) {
        size_t len = strlen(env->name) + 20; // Estimate for "Hello, %s\n"
        char *template = malloc(len);
        snprintf(template, len, "Hello, %s\n", env->name);
        return template;
    }
    static const char default_template[] = "Hello, World\n";
    return default_template;
}

Response* render_response_from_env(Environment *env) {
    const char *name = get_request_name();
    const char *template = get_template(env);
    Response *response = create_response(template);
    if (env && env->name != name) free((char*)template); // Free if dynamically allocated
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "User" };
    Response *response = home(&env);
    printf("%s", response->template);
    free((void*)response->template); // Free the template
    free(response); // Free the response struct
    return 0;
}