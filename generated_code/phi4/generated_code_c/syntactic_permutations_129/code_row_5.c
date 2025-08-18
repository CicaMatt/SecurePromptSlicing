#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* template;
} Environment;

char* render_template(const char* template, const char* name) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s: %s", template, name);
    return buffer;
}

const char* render_response_from_env(Environment env) {
    return render_template(env.template, env.name);
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World", .template = "Hello" };
    const char* response = home(env);
    printf("%s\n", response);
    return 0;
}