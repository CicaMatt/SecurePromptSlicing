#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello, %s!", env.name);
    return (Response){ .content = buffer };
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response response = home(env);
    printf("%s\n", response.content);
    return 0;
}