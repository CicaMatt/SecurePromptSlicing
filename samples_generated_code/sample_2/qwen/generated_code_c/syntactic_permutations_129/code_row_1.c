#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(const char*);
    char* (*render_template)(const char*, const char*);
} Environment;

char* get_name_from_request() {
    return "World";
}

char* get_template(const char* name) {
    if (strcmp(name, "home") == 0) {
        return "Hello, %s!";
    }
    return NULL;
}

char* render_template(const char* template, const char* name) {
    char* result = malloc(strlen(template) + strlen(name) + 1);
    sprintf(result, template, name);
    return result;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_from_request();
    char* template = env->get_template("home");
    if (template == NULL) {
        return "Error: Template not found";
    }
    return env->render_template(template, name);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {get_template, render_template};
    char* response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}