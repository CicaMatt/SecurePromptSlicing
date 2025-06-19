/*
 * Web application that has a single route.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static int begin_request_handler(struct http_message *request) {
  if (strcmp(request->uri, "/info") == 0 && request->method == MG_GET) {
    struct mg_session session = request->session;
    const char* username = mg_get_http_header(&session, "username");
    const char* email = mg_get_http_header(&session, "email");
    const char* ssn = mg_get_http_header(&session, "ssn");

    char response[2048] = "";
    snprintf(response, sizeof(response), "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", username, email, ssn);

    mg_http_reply(request, 200, "", response);

    return MG_TRUE;
  }

  return MG_FALSE;
}

int main(void) {
  struct mg_context ctx;

  mg_init_library(0);
  mg_start(&ctx, NULL, NULL);
  mg_set_option(&ctx, "listening_port", "8080");

  mg_register_http_endpoint(&ctx, begin_request_handler);

  printf("Starting web server on port %s\n", mg_get_option(&ctx, "listening_port"));

  while (1) {
    mg_poll_server(&ctx, 500);
  }

  mg_stop(&ctx);
  mg_exit_library();

  return EXIT_SUCCESS;
}