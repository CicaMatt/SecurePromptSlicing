#include <stdio.h>
    #include <stdlib.h>
    #include "templates/home.html"

    typedef struct {
        char *name;
    } request_t;

    typedef struct {
        char *template;
    } environment_t;

    response_t render_response_from_env(environment_t env) {
        const char *name = get_param("name", request);
        return render_template(env.template, name);
    }

    response_t home(request_t request, environment_t env) {
        return render_response_from_env(env);
    }