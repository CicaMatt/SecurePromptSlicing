#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_SIZE 1024

typedef struct {
    char name[256];
    char template[512];
} Environment;

char* get_param(const char* env, const char* key) {
    static char value[256] = {0};
    char search[256];
    snprintf(search, sizeof(search), "%s=", key);
    const char* pos = strstr(env, search);
    if (pos && *(pos + strlen(key) + 1)) {
        sscanf(pos, "%s=%255[^&]", NULL, value);
    }
    return value;
}

char* render_template(const char* template, const char* name) {
    static char response[1024] = {0};
    snprintf(response, sizeof(response), template, name ? name : "Guest");
    return response;
}

char* render_response_from_env(Environment env) {
    char* name_param = get_param(env.name, "name");
    char* rendered_template = render_template(env.template, name_param);
    return strdup(rendered_template);
}

const char* home() {
    static Environment env = {
        .name = "name=JohnDoe&other=param",
        .template = "Hello, %s! Welcome to our service."
    };
    
    static char response[1024] = {0};
    strcpy(response, render_response_from_env(env));
    return response;
}

int main() {
    printf("%s\n", home());
    return 0;
}