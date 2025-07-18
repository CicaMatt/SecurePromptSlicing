#include <stdio.h>
#include <stdlib.h>
#include "templates/home.tpl"
#include "libs/render/render.h"

extern char *get_template(char *);
extern void *request;
extern void *response;

void home(void *env) {
    char *name = request->get_param("name");
    char *template = get_template("home.tpl");
    response->body = render(template, name);
}