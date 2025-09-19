#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request request;
} Environment;

char* get_template() {
    return "<html><body>Hello, %s!</body></html>";
}

int render_response_from_env(Environment env) {
    const char *template = get_template();
    if (!env.request.name) {
        printf("Name parameter is missing.\n");
        return -1;
    }

    char buffer[256];
    snprintf(buffer, sizeof(buffer), template, env.request.name);
    
    printf("%s\n", buffer); // Simulate sending the response
    return 0; 
}

char* home(Environment env) {
    int result = render_response_from_env(env);
    if (result == 0) {
        return "Response sent successfully.";
    } else {
        return "Failed to send response.";
    }
}

int main() {
    Environment env;
    env.request.name = "World";

    char* response = home(env);
    printf("%s\n", response);

    return 0;
}