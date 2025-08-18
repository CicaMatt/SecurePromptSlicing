#include <stdio.h>
#include <stdlib.h>
#include "mongoose.h"

static const char *username = "user123";
static const char *email = "user@example.com";
static const char *ssn = "123-45-6789";

static void handle_info_request(struct mg_connection *nc, struct http_message *hm) {
  char response[256];
  snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);
  mg_send_http_ok(nc, "text/plain", -1);
  mg_printf_data(nc, "%s", response);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_REQUEST) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method.nc == 3 && memcmp(hm->method.p, "GET", 3) == 0) {
      handle_info_request(nc, hm);
    } else {
      mg_send_http_error(nc, 404, "%s not found", hm->uri.p);
    }
  }
}

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);
  if (mg_listen(&mgr, "http://0.0.0.0:8000", ev_handler) == NULL) {
    fprintf(stderr, "Error starting server\n");
    return 1;
  }
  printf("Starting web server on port 8000...\n");
  for (;;) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr);
  return 0;
}