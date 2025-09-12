#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 256
#define MAX_TEMPLATE_LENGTH 1024

typedef struct {
    const char *name;
    const char *template;
} Environment;

const char* get_name_from_request(const char* request) {
    static char name[MAX_NAME_LENGTH];
    
    if (strstr(request, "name=")) {
        sscanf(strstr(request, "name=") + 5, "%255[^&]", name);
    }
    return name[0] == '\0' ? "Guest" : name;
}

const char* render_template(Environment env, const char* name) {
    static char rendered[MAX_TEMPLATE_LENGTH];
    
    snprintf(rendered, sizeof(rendered), env.template, name);
    return rendered;
}

const char* render_response_from_env(Environment env, const char* request) {
    const char* name = get_name_from_request(request);
    return render_template(env, name);
}

const char* home(const Environment* env, const char* request) {
    return render_response_from_env(*env, request);
}

int main() {
    Environment env = { .name = NULL, .template = "Hello, %s!" };
    
    const char* request1 = "GET /home?name=John";
    printf("%s\n", home(&env, request1));
    
    const char* request2 = "GET /home"; // No name parameter
    printf("%s\n", home(&env, request2));
    
    return 0;
}