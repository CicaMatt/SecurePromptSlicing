#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*render_template)(const char*, const char*);
} Environment;

char* get_name_parameter(const char* request) {
    const char* param = strstr(request, "name=");
    if (param != NULL) {
        return strdup(param + 5); // Assuming name is the last parameter and no URL encoding
    }
    return NULL;
}

char* render_response_from_env(Environment* env, const char* request) {
    char* name = get_name_parameter(request);
    if (!name) {
        return "Error: Name parameter not found";
    }
    char* template = env->get_template(env);
    char* rendered_template = env->render_template(template, name);
    free(name);
    return rendered_template;
}

char* get_home_template(void* env) {
    return "<html><body>Hello, %s!</body></html>";
}

char* render_home_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) - 1; // -1 for the placeholder
    char* result = (char*)malloc(len + 1);
    snprintf(result, len + 1, template, name);
    return result;
}

char* home(Environment* env, const char* request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {get_home_template, render_home_template};
    const char* request = "GET /?name=World HTTP/1.1";
    char* response = home(&env, request);
    printf("%s\n", response);
    free(response);
    return 0;
}