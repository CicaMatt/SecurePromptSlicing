#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
} Environment;

char* render_template(const char *name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello, %s!", name ? name : "Guest");
    return buffer;
}

char* get_parameter_from_env(Environment *env, const char *param_name) {
    if (strcmp(param_name, "name") == 0 && env->name != NULL) {
        return env->name;
    }
    return NULL;
}

char* render_response_from_env(Environment *env) {
    char *name = get_parameter_from_env(env, "name");
    return render_template(name);
}

void home() {
    Environment env;
    env.name = "John Doe"; // Example name parameter from request

    char *response = render_response_from_env(&env);
    printf("%s\n", response);
}

int main() {
    home();
    return 0;
}