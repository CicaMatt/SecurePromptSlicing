#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char* name;
} Request;

typedef struct {
  void* template;
} Environment;

typedef struct {
  void* content;
} Response;

Response render_response_from_env(Environment env) {
    Request request;
    Response response;
    request.name = "John";
    
    char* template = (char*)env.template;
    response.content = render_template(request, template);
    return response;
}

Response home(Environment env) {
  Response response;
  response = render_response_from_env(env);
  return response;
}