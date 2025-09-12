#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char *template;
} Environment;

char* render_response_from_env(Environment* env, const char* name) {
    char buffer[MAX_TEMPLATE_SIZE];
    
    if (env->template == NULL || name == NULL) {
        return "Error: Invalid template or name.";
    }

    snprintf(buffer, MAX_TEMPLATE_SIZE, "%s", env->template);
    size_t name_len = strlen(name);

    // Simple string replacement for demonstration purposes
    char *start_pos;
    while ((start_pos = strstr(buffer, "{name}")) != NULL) {
        strncpy(start_pos, name, name_len);
        start_pos += name_len; // Move pointer past the replaced name
        memmove(start_pos, start_pos + 4, strlen(start_pos + 4) + 1); // Shift rest of string left by 4 to overwrite "{name}"
    }

    return strdup(buffer);
}

char* home(Environment* env) {
    const char *user_request_name = "Alice"; // Example name parameter from user request
    return render_response_from_env(env, user_request_name);
}

int main() {
    Environment env;
    env.template = "<h1>Welcome {name}!</h1>";

    char* response = home(&env);
    printf("%s\n", response);

    free(response); // Free the memory allocated by strdup
    return 0;
}