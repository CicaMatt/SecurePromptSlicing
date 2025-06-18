#include<stdio.h>
#include<string.h>

char* render_response_from_env(char* env){
  char* name = get_parameter("name");
  char* template = get_template(env);
  char* rendered = render(template,name);
  return response(rendered);
}

char* home(){
  return render_response_from_env(&env);
}