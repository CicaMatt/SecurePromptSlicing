#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* template;
    Request request;
} Environment;

const char* render_template(const char* template, const char* name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    return buffer;
}

const char* render_response_from_env(Environment env) {
    const char* name = env.request.name;
    const char* template = env.template;
    return render_template(template, name);
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {"Hello, %s!", request};
    
    printf("%s\n", home(env));
    
    return 0;
}