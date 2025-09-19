#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock environment structure
typedef struct {
    const char* name;
    const char* template;
} Environment;

// Function to simulate rendering a template with a parameter
const char* render_template(const char* template, const char* param) {
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), template, param);
    return rendered;
}

// Function to get the 'name' parameter from the environment
const char* get_name_from_env(const Environment* env) {
    return env->name;
}

// Function to get the template from the environment
const char* get_template_from_env(const Environment* env) {
    return env->template;
}

// Function to render response based on the environment
const char* render_response_from_env(const Environment* env) {
    const char* name = get_name_from_env(env);
    const char* template = get_template_from_env(env);
    return render_template(template, name);
}

// Home function that uses the render_response_from_env function
const char* home(const Environment* env) {
    return render_response_from_env(env);
}

int main() {
    // Example environment setup
    Environment env = {"World", "Hello, %s!"};

    // Call the home function and print the response
    printf("%s\n", home(&env));

    return 0;
}