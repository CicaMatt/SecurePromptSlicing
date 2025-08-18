#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_parameter)(const char* param_name);
    const char* (*get_template)(void);
} Environment;

typedef struct {
    const char* content;
} Response;

const char* get_parameter_example(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return NULL;
}

const char* get_template_example(void) {
    return "Hello, %s!";
}

Response render_response_from_env(Environment* env) {
    const char* name = env->get_parameter("name");
    const char* template = env->get_template();
    
    char* rendered_content = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered_content, template, name);

    Response response;
    response.content = rendered_content;
    return response;
}

Response home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.get_parameter = get_parameter_example;
    env.get_template = get_template_example;

    Response response = home(&env);
    printf("%s\n", response.content);

    free((void*)response.content);
    return 0;
}