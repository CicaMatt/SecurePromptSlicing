#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    Request* request;
} Environment;

char* render_template(const char* name) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "<html><body><h1>Hello, %s!</h1></body></html>", name);
    return buffer;
}

char* render_response_from_env(Environment* env) {
    const char* name = env->request->name;
    return render_template(name);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {&request};
    
    char* response = home(&env);
    printf("%s\n", response);

    return 0;
}