#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_TEMPLATE_LENGTH 500

char* get_name_from_request() {
    // Simulate getting name from request
    return "John Doe";
}

char* get_template_from_env() {
    // Simulate getting template from environment
    return "<html><body>Hello, %s!</body></html>";
}

char* render_response_from_env(char* env) {
    char* name = get_name_from_request();
    char* template = get_template_from_env();
    static char response[MAX_TEMPLATE_LENGTH];
    
    snprintf(response, MAX_TEMPLATE_LENGTH, template, name);
    return response;
}

char* home() {
    char* env = "dummy_env"; // Simulate environment
    return render_response_from_env(env);
}

int main() {
    char* response = home();
    printf("%s\n", response);
    return 0;
}