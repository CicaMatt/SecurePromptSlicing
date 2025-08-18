#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

char* get_name_from_request() {
    // Simulate getting name from request
    return "John Doe";
}

char* get_template_from_env() {
    // Simulate getting template from environment
    return "Hello, %s!";
}

char* render_response_from_env(char* env) {
    char* name = get_name_from_request();
    char* template = get_template_from_env();
    static char response[200];

    snprintf(response, sizeof(response), template, name);
    return response;
}

char* home(char* env) {
    return render_response_from_env(env);
}

int main() {
    char env[] = "dummy_environment";
    printf("%s\n", home(env));
    return 0;
}