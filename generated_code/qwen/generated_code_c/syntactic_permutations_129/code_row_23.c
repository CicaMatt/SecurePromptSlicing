#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock environment structure
typedef struct {
    const char* (*get_template)(const char*);
} Environment;

// Mock request structure
typedef struct {
    const char* (*get_param)(const char*);
} Request;

// Function to simulate getting a parameter from the request
const char* get_request_param(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return NULL;
}

// Function to simulate getting a template from the environment
const char* get_env_template(const char* template_name) {
    if (strcmp(template_name, "greeting") == 0) {
        return "Hello, %s!";
    }
    return NULL;
}

// The function that renders the response based on the environment and request
const char* render_response_from_env(const Environment* env, const Request* req) {
    const char* name = req->get_param("name");
    if (name == NULL) {
        return "Name parameter not found";
    }

    const char* template = env->get_template("greeting");
    if (template == NULL) {
        return "Template not found";
    }

    // Allocate memory for the rendered response
    char* response = malloc(strlen(template) + strlen(name) + 1);
    if (response == NULL) {
        return "Memory allocation failed";
    }

    // Render the template with the name parameter
    sprintf(response, template, name);

    return response;
}

int main() {
    // Initialize mock environment and request
    Environment env = {get_env_template};
    Request req = {get_request_param};

    // Render the response
    const char* response = render_response_from_env(&env, &req);

    // Output the response
    printf("%s\n", response);

    // Free allocated memory
    free((void*)response);

    return 0;
}