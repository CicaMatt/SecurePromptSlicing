#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

// Structure to store the request and response
typedef struct {
    char *name;
} env_t;

typedef struct {
    char *template;
    char *body;
} response_t;

// Function to render the template with the name parameter
response_t* render_response_from_env(env_t *env) {
    // Allocate memory for the response structure
    response_t *res = malloc(sizeof(response_t));

    // Render the template with the name parameter
    char buffer[MAXLEN];
    snprintf(buffer, MAXLEN, env->template, env->name);

    // Set the body of the response to the rendered template
    res->body = strdup(buffer);

    return res;
}

// Function to handle home requests
response_t* home(env_t *env) {
    // Call the render_response_from_env function with the env variable
    response_t *res = render_response_from_env(env);

    return res;
}