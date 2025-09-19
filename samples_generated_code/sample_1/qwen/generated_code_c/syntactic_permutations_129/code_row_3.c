#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_name)(void);
    char* (*get_template)(void);
} Environment;

typedef struct {
    char* content;
} Response;

char* get_name_example() {
    return "John Doe";
}

char* get_template_example() {
    return "Hello, %s!";
}

Environment create_environment() {
    Environment env;
    env.get_name = get_name_example;
    env.get_template = get_template_example;
    return env;
}

Response render_response_from_env(Environment env) {
    char* name = env.get_name();
    char* template = env.get_template();
    
    Response response;
    response.content = malloc(100 * sizeof(char));
    snprintf(response.content, 100, template, name);
    
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = create_environment();
    Response response = home(env);
    
    printf("%s\n", response.content);
    
    free(response.content);
    
    return 0;
}