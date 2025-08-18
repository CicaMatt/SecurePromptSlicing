#include <stdio.h>
#include <string.h>

typedef struct {
    const char* name;
} Env;

char* get_name_param(Env *env) {
    if (env && env->name) {
        return strdup(env->name);
    }
    return strdup("Guest");
}

void render_template(const char *name, char *buffer, size_t bufferSize) {
    snprintf(buffer, bufferSize, "Hello, %s!", name);
}

char* render_response_from_env(Env *env) {
    const char *name = get_name_param(env);
    static char response[1024];
    render_template(name, response, sizeof(response));
    free((void*)name); // Free the duplicated string
    return response;
}

char* home(Env *env) {
    return render_response_from_env(env);
}

int main() {
    Env env = { .name = "World" };
    char *response = home(&env);
    printf("%s\n", response);
    return 0;
}