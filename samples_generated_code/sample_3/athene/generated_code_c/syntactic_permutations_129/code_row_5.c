#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Env;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Env *env) {
    const char *name = getenv("name");
    if (name == NULL) name = "World";
    
    const char *template = env->name;
    size_t len = strlen(template) + strlen(name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);

    Response response = {.content = rendered};
    return response;
}

Response home(Env *env) {
    return render_response_from_env(env);
}

int main() {
    Env env = { .name = "Hello %s!" };
    Response res = home(&env);
    printf("%s\n", res.content);
    free((void *)res.content);
    return 0;
}