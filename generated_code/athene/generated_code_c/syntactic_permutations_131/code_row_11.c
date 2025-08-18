#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* (*get_template)(const char*);
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env, const char* name) {
    const char* template = env.get_template(name);
    return (Response){.content = template};
}

Response home(Environment env) {
    return render_response_from_env(env, "home");
}

// Mock implementation for testing
const char* get_home_template(const char* name) {
    if (name && strcmp(name, "home") == 0) {
        return "<h1>Welcome Home</h1>";
    }
    return NULL;
}

int main() {
    Environment env = {.get_template = get_home_template};
    Response response = home(env);
    printf("%s\n", response.content);
    return 0;
}