#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

typedef struct {
    const char *template;
} Response;

Response render_template_with_name(const char *name) {
    Response response;
    asprintf(&response.template, "Hello, %s!", name);
    return response;
}

Response render_response_from_env(Environment env) {
    if (!env.name || strlen(env.name) == 0) {
        const char *default_message = "Hello, guest!";
        Response response = { .template = default_message };
        return response;
    }
    
    return render_template_with_name(env.name);
}

Response home() {
    Environment env = { .name = getenv("USER_NAME") ?: "guest" };
    return render_response_from_env(env);
}

int main() {
    Response response = home();
    printf("%s\n", response.template);
    free((void *)response.template);
    return 0;
}