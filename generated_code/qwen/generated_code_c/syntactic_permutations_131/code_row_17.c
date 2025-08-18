#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define TEMPLATE_FORMAT "Hello, %s!"

typedef struct {
    char *name;
} Environment;

char* render_response_from_env(Environment env) {
    static char response[256];
    snprintf(response, sizeof(response), TEMPLATE_FORMAT, env.name);
    return response;
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = malloc(sizeof(char) * MAX_NAME_LENGTH);

    if (env.name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter name: ");
    if (fgets(env.name, MAX_NAME_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        env.name[strcspn(env.name, "\n")] = '\0';
    } else {
        fprintf(stderr, "Failed to read input\n");
        free(env.name);
        return 1;
    }

    char* response = home(env);
    printf("Response: %s\n", response);

    free(env.name);
    return 0;
}