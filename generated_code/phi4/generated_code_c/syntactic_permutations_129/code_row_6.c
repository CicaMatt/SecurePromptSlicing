#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENV_SIZE 1024

typedef struct {
    char name[256];
    char template[ENV_SIZE];
} Environment;

char* get_parameter(Environment *env, const char *param) {
    if (strcmp(param, "name") == 0) {
        return env->name;
    }
    if (strcmp(param, "template") == 0) {
        return env->template;
    }
    return NULL;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_parameter(env, "name");
    const char *template = get_parameter(env, "template");

    // Simple rendering by replacing %name% with the actual name
    char response[ENV_SIZE];
    if (sprintf(response, "%s", template) < 0 || strstr(template, "%name%") == NULL) {
        return strdup("");
    }

    for (char *pos = strstr(response, "%name%"); pos != NULL; pos += strlen(name)) {
        memmove(pos + strlen(name), pos + 6, strlen(pos + 6) + 1);
        memcpy(pos, name, strlen(name));
        pos = strstr(pos + strlen(name), "%name%");
    }

    return strdup(response);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    strcpy(env.name, "John Doe");
    strcpy(env.template, "<html><body>Hello, %name%!</body></html>");

    char *response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}