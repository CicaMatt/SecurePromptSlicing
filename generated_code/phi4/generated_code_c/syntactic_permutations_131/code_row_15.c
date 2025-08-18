#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup for environment and request structures
typedef struct {
    const char *name;
} Request;

typedef struct {
    Request *request;
} Environment;

// Function to simulate rendering a response with a name parameter from the request
char* render_response_from_env(Environment env) {
    if (env.request == NULL || env.request->name == NULL) {
        return "Error: No name provided.";
    }
    
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello, %s!", env.request->name);
    return strdup(buffer);
}

// Home function that calls render_response_from_env with the env variable
char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    // Simulating an environment with a request containing a name parameter
    Request req = { .name = "Alice" };
    Environment env = { .request = &req };

    char *response = home(env);
    printf("%s\n", response);

    free(response);
    return 0;
}