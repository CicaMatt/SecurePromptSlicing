#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char *response_content = malloc(len);
    snprintf(response_content, len, "%s%s", template, name);
    return (Response){.content = response_content};
}

const char* get_request_name(Environment *env) {
    return env->name;
}

const char* get_template(Environment *env) {
    // Assuming a fixed template for simplicity
    return "Hello, ";
}

Response render_response_from_env(Environment *env) {
    const char *name = get_request_name(env);
    const char *template = get_template(env);
    return render_response(template, name);
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void *)response.content); // Free allocated memory
    return 0;
}