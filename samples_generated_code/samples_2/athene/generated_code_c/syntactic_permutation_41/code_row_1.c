#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *html_template = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html\r\n\r\n"
"<html><body>"
"<h1>User Information</h1>"
"<p>Username: %s</p>"
"<p>Email: %s</p>"
"<p>Last 4 digits of SSN: %s</p>"
"</body></html>";

static void handle_info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = "user123";
    const char *email = "user@example.com";
    const char *ssn_last_4 = "1234";

    char response[1024];
    snprintf(response, sizeof(response), html_template, username, email, ssn_last_4);
    mg_send(nc, response, strlen(response));
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  struct http_message *hm = (struct http_message *) p;
  if (ev == MG_EV_HTTP_REQUEST) {
    if (mg_vcmp(&hm->uri, "/info") == 0) {
      handle_info(nc, hm);
    } else {
      mg_send_head(nc, 404, 0, "Content-Type: text/html");
      mg_printf(nc, "%s", "<html><body>Not Found</body></html>");
    }
  }
}

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  if (mg_listen(&mgr, "http://0.0.0.0:8000", ev_handler) == NULL) {
    fprintf(stderr, "Error starting server\n");
    return 1;
  }
  printf("Starting server on port 8000\n");

  while (1) {
    mg_mgr_poll(&mgr, 1000);
  }

  mg_mgr_free(&mgr);
  return 0;
}