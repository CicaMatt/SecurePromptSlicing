#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    char *template_str;
    char *response;
} Response;

Response *render_response_from_env(Environment *env) {
    char name[100] = "World";
    if (env->name != NULL) {
        strncpy(name, env->name, 99);
    }
    char template[256];
    snprintf(template, sizeof(template), "<h1>Hello, %s!</h1>", name);

    Response *resp = (Response *)malloc(sizeof(Response));
    resp->template_str = strdup(template);
    resp->response = resp->template_str;
    return resp;
}

Response *home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"John"};
    Response *response = home(&env);
    printf("%s\n", response->response);
    free(response->template_str);
    free(response);
    return 0;
}