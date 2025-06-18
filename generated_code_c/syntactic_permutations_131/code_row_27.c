#include <stdio.h>
#include <string.h>
#define MAX_NAME_LEN 63
char *render_template(char *tmpl, char name[MAX_NAME_LEN])
{
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), tmpl, name);
    return strdup(buffer);
}
void render_response_from_env(struct environment *env)
{
    struct request *req = env->request;
    char *name = req->params["name"];
    if (strlen(name) > MAX_NAME_LEN)
        return;
    char *tmpl = get_template_from_environment(env);
    char *rendered_template = render_template(tmpl, name);
    struct response *res = new_response();
    res->body = rendered_template;
    env->response = res;
}
struct environment {
    struct request *request;
    struct response *response;
};
void home(struct environment *env)
{
    render_response_from_env(env);
}