#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Environment;

const char* get_name_parameter(const Environment* env) {
    return env->name;
}

char* render_template(const char* name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "<html><body><h1>Hello, %s!</h1></body></html>", name);
    return buffer;
}

const char* render_response_from_env(Environment env) {
    const char* name = get_name_parameter(&env);
    return render_template(name);
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"World"};
    printf("%s\n", home(env));
    return 0;
}