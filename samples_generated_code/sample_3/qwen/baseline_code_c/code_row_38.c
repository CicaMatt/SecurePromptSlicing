#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "mongoose.h"

int check_url(const char *url) {
    regex_t regex;
    int reti = regcomp(&regex, "(http[s]?://)?([a-zA-Z0-9.-]*\\.)?example\\.com(/.*)?", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

void handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        const char *target = mg_get_http_var(&hm->query_string, "target", NULL);

        if (target && check_url(target)) {
            mg_http_send_redirect(nc, 302, "%s", target);
        } else {
            mg_http_send_redirect(nc, 302, "/%s", "");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", handler);

    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {}

    mg_mgr_free(&mgr);
    return 0;
}