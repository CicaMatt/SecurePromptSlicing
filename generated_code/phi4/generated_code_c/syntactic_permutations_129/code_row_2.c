#include <stdio.h>
#include <string.h>

// Mock environment structure for demonstration purposes
typedef struct {
    char *request_method;
    char *path_info;
    char **headers;
    char *body;
} Environment;

// Function to simulate getting a parameter from the request
char* get_request_parameter(Environment *env, const char *param_name) {
    if (strcmp(param_name, "name") == 0 && env->path_info != NULL) {
        return env->path_info; // Assuming path_info contains query parameters like "/?name=John"
    }
    return "";
}

// Function to simulate getting a template from the environment
char* get_template(Environment *env) {
    static char template[] = "Hello, {{ name }}!";
    return template;
}

// Function to render the template with the given parameter
char* render_template(char *template, const char *name) {
    // Create a buffer large enough for the rendered output
    size_t buf_size = strlen(template) + strlen(name) + 2; 
    char *rendered = (char *)malloc(buf_size);
    snprintf(rendered, buf_size, template, name);

    return rendered;
}

// Function to create a response with the rendered content
char* create_response(char *content) {
    static char response[1024];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", content);
    return response;
}

// Function to render and get a response from the environment
char* render_response_from_env(Environment *env) {
    char *name = get_request_parameter(env, "name");
    if (strlen(name) == 0) {
        name = "World"; // Default value for demonstration purposes
    }
    
    char *template = get_template(env);
    char *rendered_content = render_template(template, name);
    char *response = create_response(rendered_content);

    free(rendered_content); // Free the dynamically allocated memory
    return response;
}

// Home function that calls render_response_from_env and returns the response
char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { "GET", "/?name=John", NULL, "" };
    char *response = home(&env);
    printf("%s\n", response);

    return 0;
}