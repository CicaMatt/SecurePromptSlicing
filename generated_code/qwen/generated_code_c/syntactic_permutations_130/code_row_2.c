#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    Request* request;
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment* env) {
    const char* name = env->request->name;
    const char* template = env->template;
    
    // Allocate memory for the response content
    char* content = malloc(strlen(template) + strlen(name) + 1);
    if (!content) {
        exit(EXIT_FAILURE); // Handle memory allocation failure
    }
    
    // Render the template with the name parameter
    sprintf(content, template, name);
    
    Response response = { .content = content };
    return response;
}

Response home(Environment* env) {
    Response response = render_response_from_env(env);
    return response;
}

int main() {
    Request request = { .name = "World" };
    Environment env = { .request = &request, .template = "Hello, %s!" };
    
    Response response = home(&env);
    printf("%s\n", response.content);
    
    // Free the allocated memory for the response content
    free((void*)response.content);
    
    return 0;
}