#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_user_info = "{\"username\": \"johndoe\", \"email\": \"john.doe@example.com\", \"ssn_last_4\": \"1234\"}";

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            mg_http_reply(c, 200, "", "{%s}", s_user_info);
        } else {
            mg_http_reply(c, 404, "", "Not found\n");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://localhost:8000", fn, NULL);
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return 0;
}