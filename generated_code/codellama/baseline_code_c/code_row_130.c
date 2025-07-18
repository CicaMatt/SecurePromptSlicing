#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // Environment structure for storing templates and names
    struct env {
        char *tmpl;
        char *name;
    };

    // Response structure for holding rendered template
    struct response {
        char *body;
        int code;
    };

    // Function to render a template with a name from the environment
    struct response* render_response_from_env(struct env env) {
        char *tmpl = env.tmpl;
        char *name = env.name;
        int bufsize = strlen(tmpl) + strlen(name) + 1;
        char *buf = malloc(bufsize);
        sprintf(buf, tmpl, name);
        struct response *resp = malloc(sizeof(struct response));
        resp->body = buf;
        resp->code = 200;
        return resp;
    }

    // Home function calls render_response_from_env with environment and returns response
    struct response* home() {
        struct env env = {"Hello, %s!", "world"};
        return render_response_from_env(env);
    }