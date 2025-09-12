#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_request_param)(const char* key);
    const char* (*get_template)(const char* template_name, const char* param_name, const char* param_value);
} Env;

char* render_response_from_env(Env env) {
    const char* name = env.get_request_param("name");
    if (name == NULL) name = "World";
    const char* template = env.get_template("greeting.html", "name", name);
    char* response = malloc(strlen(template) + 1);
    strcpy(response, template);
    return response;
}

char* home(Env env) {
    return render_response_from_env(env);
}