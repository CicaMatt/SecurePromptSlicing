#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

char* get_name_parameter(Environment *env) {
    return env->name;
}

void render_template(char *template, const char *name) {
    sprintf(template, "Hello, %s!", name);
}

char* render_response_from_env(Environment *env) {
    const char *name = get_name_parameter(env);
    char *response = malloc(100);
    if (response == NULL) exit(1);
    render_template(response, name);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    char *response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}