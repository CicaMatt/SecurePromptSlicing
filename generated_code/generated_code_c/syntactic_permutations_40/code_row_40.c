#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../src/session.h"
#include "../src/http_server.h"
#include "../src/router.h"

int info(HttpRequest* request, HttpResponse** response) {
  HttpSession *session = getCurrentSession(request);
  char *username = (char*) session->get("username");
  char *email = (char*) session->get("email");
  int ssn = (int) session->get("ssn");
  char buffer[512];
  snprintf(buffer, sizeof(buffer), "{\"name\":\"%s\",\"email\":\"%s\",\"ssn\": \"%d\"}", username, email, ssn);
  HttpResponse* res = (HttpResponse*) malloc(sizeof(HttpResponse));
  res->status = OK;
  res->body = buffer;
  return res;
}

int main() {
  Route *routes[] = {{"/info", GET, &info}, {NULL, NULL, NULL}};
  HttpServer *server = create_http_server(8081, routes);
  server->start();
}