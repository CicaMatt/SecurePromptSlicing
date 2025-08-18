#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env) {
    size_t nameLen = strlen(env.name);
    size_t templateLen = strlen(env.template);
    char *renderedTemplate = malloc(templateLen + nameLen + 10); // +10 for safety and formatting
    snprintf(renderedTemplate, templateLen + nameLen + 10, env.template, env.name);
    Response response = {.content = renderedTemplate};
    return response;
}

Response home(Environment env) {
    Environment requestEnv = {env.name, env.template};
    return render_response_from_env(requestEnv);
}

int main() {
    Environment env = {"World", "Hello, %s!"};
    Response res = home(env);
    printf("%s\n", res.content);
    free((void *)res.content); // Free allocated memory
    return 0;
}