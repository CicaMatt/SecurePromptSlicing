#include <stdio.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} Parameter;

typedef struct {
    Parameter* parameters;
    int count;
} Environment;

const char* get_parameter_value(Environment env, const char* key) {
    for (int i = 0; i < env.count; ++i) {
        if (strcmp(env.parameters[i].key, key) == 0) {
            return env.parameters[i].value;
        }
    }
    return NULL;
}

const char* render_template(const char* template, const char* name) {
    static char response[1024];
    snprintf(response, sizeof(response), template, name);
    return response;
}

char* render_response_from_env(Environment env) {
    const char* name = get_parameter_value(env, "name");
    if (name == NULL) {
        name = "World";
    }
    const char* template = "<html><body>Hello, %s!</body></html>";
    static char response[1024];
    strcpy(response, render_template(template, name));
    return response;
}

char* home(Environment env) {
    return render_response_from_env(env);
}