#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)();
    char* (*get_parameter)(const char*);
} Environment;

char* render_template(const char* name) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Hello, %s!", name);
    return buffer;
}

char* render_response_from_env(Environment* env) {
    const char* name = env->get_parameter("name");
    const char* template = env->get_template();
    // In this example, we ignore the actual template and use a simple function
    return render_template(name);
}

Environment* create_test_environment() {
    static Environment env;
    static char test_name[] = "World";

    env.get_template = ^char*(){
        return "<html><body>{{ name }}</body></html>";
    };
    
    env.get_parameter = ^(const char* param){
        if (strcmp(param, "name") == 0) {
            return test_name;
        }
        return NULL;
    };

    return &env;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment* env = create_test_environment();
    char* response = home(env);
    printf("%s\n", response);
    return 0;
}