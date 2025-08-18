#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Env;

typedef struct {
    const char *content_type;
    const char *body;
} Response;

Response render_response_from_env(Env *env) {
    const char *name = getenv("USER_NAME"); // Assume this is set in the environment
    if (name == NULL || strlen(name) == 0) {
        name = "World";
    }
    const char *template = env->name;
    char body[256];
    snprintf(body, sizeof(body), template, name);
    Response response = {"text/html", body};
    return response;
}

Response home(Env *env) {
    return render_response_from_env(env);
}

int main() {
    Env env = { "Hello %s!" };
    Response response = home(&env);
    printf("Content-Type: %s\n\n%s", response.content_type, response.body);
    return 0;
}