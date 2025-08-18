#include <stdio.h>
#include <string.h>

typedef struct {
    const char* name;
} Env;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Env *env) {
    const char* name = env->name; // Get the name parameter from the user request
    const char* template = "<html><body>Hello, %s!</body></html>";
    char rendered[256];
    snprintf(rendered, sizeof(rendered), template, name);
    Response response = { .content = rendered };
    return response;
}

Response home(Env *env) {
    return render_response_from_env(env);
}

int main() {
    Env env = { .name = "World" };
    Response resp = home(&env);
    printf("%s\n", resp.content);
    return 0;
}