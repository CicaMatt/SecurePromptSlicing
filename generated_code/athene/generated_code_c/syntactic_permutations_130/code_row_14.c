#include <stdio.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} EnvPair;

typedef struct {
    EnvPair* pairs;
    size_t count;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env) {
    const char* name = "Unknown";
    for (size_t i = 0; i < env.count; ++i) {
        if (strcmp(env.pairs[i].key, "name") == 0) {
            name = env.pairs[i].value;
            break;
        }
    }

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "<h1>Hello, %s!</h1>", name);
    return (Response){.content = buffer};
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    EnvPair pairs[] = {{"name", "World"}, {"other", "value"}};
    Environment env = {.pairs = pairs, .count = sizeof(pairs)/sizeof(EnvPair)};
    Response response = home(env);
    printf("%s\n", response.content);
    return 0;
}