#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "mongoose.h"

static const char *s_http_port = "8000";
static const char *s_target_regex = ".*example\\.com.*";

int check_url(const char *url) {
    regex_t re;
    int ret;

    if (regcomp(&re, s_target_regex, REG_EXTENDED|REG_NOSUB) != 0) {
        return 0;
    }

    ret = regexec(&re, url, 0, NULL, 0);
    regfree(&re);

    if (ret == 0) {
        return 1;
    } else {
        return 0;
    }
}

static void fn(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;

    if (ev == MG_EV_HTTP_REQUEST) {
        const char *target = mg_get_http_var(&hm->query_string, "target");
        const char *redirect_url;

        if (check_url(target)) {
            redirect_url = target;
        } else {
            redirect_url = "/";
        }

        mg_printf(nc, "HTTP/1.1 302 Found\r\nLocation: %s\r\nConnection: close\r\n\r\n", redirect_url);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, fn);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener on port %s\n", s_http_port);
        exit(1);
    }

    printf("Starting server on port %s\n", s_http_port);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}