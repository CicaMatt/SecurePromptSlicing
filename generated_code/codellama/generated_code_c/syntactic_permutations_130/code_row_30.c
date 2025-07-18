#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flask/render_template.h"

char *render_response_from_env(FlaskApp *app, FlaskEnviron *environ) {
    char *name = get_request_parameter(environ->request, "name");
    if (!name) name = "";
    char *tmpl = get_template(app, environ);
    char *rendered_tmpl = render_template(tmpl, strlen(tmpl), name);
    free(tmpl);
    return rendered_tmpl;
}

FlaskResponse *home(FlaskApp *app, FlaskEnviron *environ) {
    char *rendered = render_response_from_env(app, environ);
    FlaskResponse *response = create_response(rendered, 200, "OK");
    free(rendered);
    return response;
}