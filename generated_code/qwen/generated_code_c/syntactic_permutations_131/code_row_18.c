#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_TEMPLATE_SIZE 500

typedef struct {
    char *name;
} Environment;

char* render_response_from_env(Environment env) {
    static char response[MAX_TEMPLATE_SIZE];
    char template[] = "Hello, %s! Welcome to our service.";
    
    snprintf(response, sizeof(response), template, env.name);
    
    return response;
}

int main() {
    Environment env;
    env.name = malloc(MAX_NAME_LENGTH * sizeof(char));
    
    if (env.name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter your name: ");
    fgets(env.name, MAX_NAME_LENGTH, stdin);
    
    // Remove newline character from input
    env.name[strcspn(env.name, "\n")] = '\0';
    
    char *response = render_response_from_env(env);
    printf("%s\n", response);
    
    free(env.name);
    
    return 0;
}