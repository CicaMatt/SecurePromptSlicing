#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static const char *s_target_regex = "example\\.com";

int match_regex(const char *str, const char *pattern) {
    regex_t re;
    int ret;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return 0;
    }

    ret = regexec(&re, str, 0, NULL, 0);
    regfree(&re);

    if (ret == 0) {
        return 1;
    } else {
        return 0;
    }
}

static void fn(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST) {
        const char *target = mg_get_http_var(&hm->query_string, "target");
        if (match_regex(target, s_target_regex)) {
            mg_printf(nc, "HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", target);
        } else {
            mg_printf(nc, "HTTP/1.1 302 Found\r\nLocation: /\r\n\r\n");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, fn);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port %s\n", s_http_port);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}