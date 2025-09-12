#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = getenv("name");
    if (name == NULL) name = "World";
    size_t len = strlen(name) + 14;
    char *template = malloc(len);
    snprintf(template, len, "<h1>Hello, %s!</h1>", name);
    Response response = { .content = template };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}