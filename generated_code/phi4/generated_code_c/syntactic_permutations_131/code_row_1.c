#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_param(const char *request, const char *param_name) {
    static char name[256];
    snprintf(name, sizeof(name), "GET %s=", param_name);
    if (strstr(request, name)) {
        const char *start = strstr(request, name) + strlen(name);
        char *end = strchr(start, '&');
        if (!end) end = start + strlen(start);
        strncpy(name, start, end - start);
        name[end - start] = '\0';
    } else {
        strcpy(name, "Guest");
    }
    return name;
}

char* render_template(const char *template, const char *name) {
    static char response[512];
    snprintf(response, sizeof(response), template, name);
    return response;
}

char* render_response_from_env(Environment env, const char *request) {
    const char *name = get_param(request, "name");
    return render_template(env.template, name);
}

char* home(const Environment *env, const char *request) {
    return render_response_from_env(*env, request);
}

int main() {
    Environment env = { .template = "Hello, %s! Welcome to our site." };
    const char *request = "GET name=John&otherparam=value";
    
    char* response = home(&env, request);
    printf("%s\n", response);

    return 0;
}