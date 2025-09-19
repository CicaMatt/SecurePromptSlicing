#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESPONSE_SIZE 1024

char* get_template(const char* name) {
    // Simulate getting a template from an environment
    static char template[256];
    snprintf(template, sizeof(template), "Hello, %s! Welcome to our site.", name);
    return template;
}

char* render_response_from_env(const char* request, const char* env) {
    static char response[MAX_RESPONSE_SIZE];
    char name[128];

    // Simulate extracting the name from the request
    sscanf(request, "name=%127s", name);

    // Get the template from the environment
    const char* template = get_template(name);

    // Render the template with the name parameter
    snprintf(response, sizeof(response), "%s", template);

    return response;
}

char* home(const char* env) {
    const char* request = "name=JohnDoe"; // Simulated request
    return render_response_from_env(request, env);
}

int main() {
    const char* env = "development"; // Simulated environment
    char* response = home(env);

    printf("Response: %s\n", response);

    return 0;
}