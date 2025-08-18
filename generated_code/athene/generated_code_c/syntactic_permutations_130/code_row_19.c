#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Env;

char* get_query_param(const char *query, const char *key) {
    char param[256] = "";
    sscanf(query, "%[^&]", param);
    if (strncmp(param, key, strlen(key)) == 0) {
        return param + strlen(key) + 1;
    }
    return NULL;
}

char* render_response_from_env(Env *env) {
    const char *name = get_query_param(env->name, "name");
    char response[512];
    snprintf(response, sizeof(response), env->template, name ? name : "World");
    return strdup(response);
}

void home(Env *env, char **response) {
    *response = render_response_from_env(env);
}

int main() {
    Env env = {"?name=John", "Hello, %s!"};
    char *response;
    home(&env, &response);
    printf("%s\n", response);
    free(response);
    return 0;
}