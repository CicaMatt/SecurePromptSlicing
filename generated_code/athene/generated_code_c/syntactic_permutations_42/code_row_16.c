#include <stdio.h>
#include <stdlib.h>
#include "mongoose.h"

static const char *s_http_port = "8080";

static void info(struct mg_connection *nc, struct http_message *hm) {
  const char *username = mg_get_cookie(hm, "username");
  const char *email = mg_get_cookie(hm, "email");
  const char *ssn = mg_get_cookie(hm, "ssn");

  if (username != NULL && email != NULL && ssn != NULL) {
    char response[256];
    snprintf(response, sizeof(response), 
             "Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);
    mg_send_http_ok(nc, "text/plain", -1);
    mg_printf(nc, "%s", response);
  } else {
    mg_send_http_error(nc, 400, "User information not available");
  }
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  struct http_message *hm = (struct http_message *) p;
  if (ev == MG_EV_HTTP_REQUEST) {
    if (mg_vcmp(&hm->uri, "/info") == 0) {
      info(nc, hm);
    } else {
      mg_send_http_error(nc, 404, "Not found");
    }
  }
}

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  printf("Starting HTTP server on port %s\n", s_http_port);
  mg_http_listen(&mgr, s_http_port, ev_handler, NULL);
  for (;;) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr);
  return 0;
}