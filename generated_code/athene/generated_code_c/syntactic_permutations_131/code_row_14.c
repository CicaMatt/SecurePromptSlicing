#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
} Env;

char* get_parameter(Env *env) {
    return env->name;
}

void render_template(char *template, const char *name) {
    sprintf(template, "Hello, %s!", name);
}

char* render_response_from_env(Env *env) {
    char *name = get_parameter(env);
    static char response[100];
    render_template(response, name);
    return response;
}

char* home(Env *env) {
    return render_response_from_env(env);
}

int main() {
    Env env = {"World"};
    printf("%s\n", home(&env));
    return 0;
}