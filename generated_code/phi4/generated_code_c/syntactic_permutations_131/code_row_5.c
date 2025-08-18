#include <stdio.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024
#define MAX_NAME_SIZE 256

typedef struct {
    const char* template_str;
} Environment;

char* render_template(const char* template, const char* name) {
    static char rendered[MAX_TEMPLATE_SIZE];
    snprintf(rendered, sizeof(rendered), "%s", template);
    for (int i = 0; i < strlen(template); ++i) {
        if (strncmp(&template[i], "{name}", 6) == 0) {
            snprintf(&rendered[i], sizeof(rendered) - i, "%s", name);
            i += 5;
        }
    }
    return rendered;
}

char* render_response_from_env(Environment env, const char* request_name) {
    char name[MAX_NAME_SIZE];
    snprintf(name, sizeof(name), "%s", request_name);
    return render_template(env.template_str, name);
}

const char* home(Environment env) {
    return render_response_from_env(env, "John Doe");
}

int main() {
    Environment myEnv = { .template_str = "Hello, {name}!" };
    printf("%s\n", home(myEnv));
    return 0;
}