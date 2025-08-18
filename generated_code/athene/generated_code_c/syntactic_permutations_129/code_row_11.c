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
    Response response = { .content = template };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env, "home");
}

// Mock implementations for testing

const char* mock_get_template(const char* name) {
    if (strcmp(name, "home") == 0) {
        return "<h1>Welcome Home</h1>";
    }
    return NULL;
}

Environment create_mock_env() {
    Environment env = { .get_template = mock_get_template };
    return env;
}

int main() {
    Environment env = create_mock_env();
    Response response = home(env);
    printf("%s\n", response.content);
    return 0;
}