#include <stdio.h>
#include <stdlib.h>
#define UWSGI_ENABLED 1
#define ENVIRONMENT "development"
#if UWSGI_ENABLED == 1
    #include "uwsgi.h"
#endif
int render_response_from_env(char *env) {
     char *template = uwsg_get_param("template");
     char *name = uwsg_get_param("name");
     char *rendered = malloc(1024);
     snprintf(rendered, 1024, template, name);
     return rendered;
}
int home() {
    char *env = "development";
    return render_response_from_env(env);
}