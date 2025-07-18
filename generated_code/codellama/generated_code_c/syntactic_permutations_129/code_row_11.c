#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "templates/home.html.h"

char *render_response_from_env(environ *env) {
    char *name = env->GET["name"];
    return response(200, home(name), "text/html");
}

char *home(const char *name) {
    return templates_home_html("{{name}}", name);
}