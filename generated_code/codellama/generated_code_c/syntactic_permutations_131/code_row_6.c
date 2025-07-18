#include <stdio.h>
 #include <stdlib.h>
 #include "render_template.h"
 
 char* render_response_from_env(char *name, char *env){
     char *template = get_template_from_env(env);
     char *rendered_template = render_template(template, name);
     return rendered_template;
 }
 
 char* home(char *env) {
     char name[1024];
     printf("What is your name? ");
     fgets(name, sizeof(name), stdin);
     char *response = render_response_from_env(name, env);
     return response;
 }
 
 int main() {
     char env[1024];
     printf("What is the environment? ");
     fgets(env, sizeof(env), stdin);
     char *response = home(env);
     printf("%s", response);
     return 0;
 }