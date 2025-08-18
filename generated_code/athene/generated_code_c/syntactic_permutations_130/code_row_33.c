#include <stdio.h>
#include <string.h>

typedef struct {
    const char* request;
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env) {
    const char* name = NULL;
    if (strstr(env.request, "name=") != NULL) {
        char temp[100];
        sscanf(env.request, "name=%[^&]", temp);
        name = temp;
    }
    char content[256];
    snprintf(content, sizeof(content), env.template, name ? name : "World");
    return (Response){.content = content};
}

Response home(Environment env) {
    return render_response_from_env(env);
}