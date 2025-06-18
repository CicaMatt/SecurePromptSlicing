#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http/http.h"

char *render_template(char *name, char *template) {
  int i = 0;
  while (template[i] != '\0') {
    if (template[i] == '{') {
      int j = 1;
      while (j > 0 && template[i + j] != '\0') {
        if (template[i + j] == '}')
          --j;
        else if (template[i + j] == '{')
          ++j;
        ++j;
      }
      char *key = strndup(template + i + 1, j - 1);
      char *value = get_env(name, key);
      template[i] = '\0';
      char *result = strdup(template);
      if (value != NULL) {
        result = realloc(result, sizeof(char) * (strlen(result) + 1 + strlen(value) + 1));
        strcat(result, value);
        strcat(result, template + i + j + 2);
      } else {
        strcat(result, template + i + 1);
      }
      free(key);
      free(template);
      template = result;
    }
    ++i;
  }
  return template;
}

char *render_response_from_env(http_request *req, http_response *res, env *env) {
  char *name = get_param("name", req);
  char *template = get_template(env);
  char *body = render_template(name, template);
  response *resp = new_response();
  resp->code = 200;
  resp->body = body;
  return resp;
}

char *home(http_request *req, http_response *res, env *env) {
  return render_response_from_env(req, res, env);
}