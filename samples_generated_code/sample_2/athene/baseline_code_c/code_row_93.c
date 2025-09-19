#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = getenv("USER_NAME"); // Simulating getting name from request
    if (name == NULL) name = "Guest";
    const char *template = env->name; // Assuming environment holds the template

    size_t content_length = strlen(template) + strlen(name) + 20;
    char *content = malloc(content_length);
    snprintf(content, content_length, "%s, %s!", template, name);

    Response response = { .content = content };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "Hello" };
    Response res = home(&env);
    printf("%s\n", res.content);
    free((void *)res.content); // Free allocated memory
    return 0;
}