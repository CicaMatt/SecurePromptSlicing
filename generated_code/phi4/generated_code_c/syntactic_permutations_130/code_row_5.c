#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

typedef struct {
    char name[MAX_NAME_LENGTH];
    char template[1024];
} Environment;

char *render_template(const char *template_str, const char *name) {
    char *result = (char *)malloc(strlen(template_str) + strlen(name) + 1);
    if (result == NULL) {
        return NULL;
    }
    sprintf(result, "%s", template_str);
    size_t pos = strstr(result, "{% name %}"). - result;
    memmove(result + pos + strlen(name), result + pos, strlen(result) - pos + 1);
    memcpy(result + pos, name, strlen(name));
    return result;
}

char *render_response_from_env(Environment env) {
    char *response = render_template(env.template, env.name);
    if (response == NULL) {
        response = strdup("Error rendering template.");
    }
    return response;
}

char *home(char *env_json) {
    Environment env;
    sscanf(env_json, "{\"name\":\"%[^"]\",\"template\":\"%[^\"]\"}", env.name, env.template);

    char *response = render_response_from_env(env);
    return response;
}

int main() {
    // Example environment
    char *env_json = "{\"name\":\"John Doe\",\"template\":\"Hello, {% name %}! Welcome to the site.\"}";

    char *response = home(env_json);
    printf("%s\n", response);

    free(response);
    return 0;
}