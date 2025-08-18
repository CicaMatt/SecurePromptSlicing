#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static const int s_max_url_size = 1024;

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        char url[s_max_url_size];
        const char *target;

        if (mg_vsnprintf(url, sizeof(url), "/%.*s", hm->message.len - 1, hm->body.p + 1) == NULL) {
            mg_http_error(nc, 500, "Internal Server Error");
            return;
        }

        target = strstr(url, "?target=");
        if (target != NULL) {
            target += strlen("?target=");

            const char *regex_pattern = "^.*example\\.com.*$";
            int regex_match = 0;

            regmatch_t pmatch[1];
            regcomp_t re;
            regcomp(&re, regex_pattern, REG_EXTENDED);
            
            if (regexec(&re, target, 1, pmatch, 0) == 0) {
                regex_match = 1;
            }
            regfree(&re);

            if (regex_match) {
                mg_send_redirect(nc, target);
            } else {
                mg_http_error(nc, 400, "Bad Request");
            }
        } else {
            mg_serve_http(nc, hm, s_http_port);
        }
    }
}

int main(int argc, char *argv[]) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, ev_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    printf("Starting web server on port %s\n", s_http_port);

    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}


To compile and run this code:

1. Install Mongoose: `https://github.com/cesanta/mongoose`
2. Compile with:
   
   gcc -o webapp webapp.c mongoose.h mongoose.c -lpthread -lm
   
3. Run the executable:
   
   ./webapp
   

Navigate to `http://localhost:8000/?target=<your-target-url>` to test.