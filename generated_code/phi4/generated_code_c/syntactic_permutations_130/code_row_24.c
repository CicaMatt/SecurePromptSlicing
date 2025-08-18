#include <stdio.h>
#include <string.h>

typedef struct {
    char *request_method;
    char *query_string;
} Request;

typedef struct {
    const char *name;
    int value;
} EnvironmentVariable;

typedef struct {
    Request request;
    EnvironmentVariable env_vars[10];
    int num_env_vars;
} Environment;

char* render_template(const char* template, const char* name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s: %s", template, name);
    return buffer;
}

char* get_query_param(const char *query_string, const char *param_name) {
    static char param_value[256] = "";
    if (strstr(query_string, param_name)) {
        sscanf(strstr(query_string, param_name) + strlen(param_name), "=%s", param_value);
    }
    return param_value;
}

char* render_response_from_env(Environment env) {
    const char *template = "Hello, ";
    const char *query_string = env.request.query_string;

    if (strcmp(env.request.request_method, "GET") == 0 && query_string != NULL) {
        const char *name_param = get_query_param(query_string, "name");
        
        if (*name_param) {
            return render_template(template, name_param);
        }
    }

    return render_template(template, "Guest");
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.request.request_method = "GET";
    env.request.query_string = "name=JohnDoe";
    env.num_env_vars = 0;

    char *response = home(env);
    printf("%s\n", response);

    return 0;
}