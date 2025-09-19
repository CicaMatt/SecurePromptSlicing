#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static struct mg_serve_http_opts s_http_opts;

void handle_request(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        const char *uri = hm->uri.p;
        
        if (strcmp(uri + 1, "api") == 0 && mg_vcmp(&hm->method, (const char *)&MHD_GET) == 0) {
            // Parse query string
            struct mg_str qs = { .p = hm->query_string.p, .len = hm->query_string.len };
            const char *name_value = NULL;
            
            if (qs.len > 0) {
                char *qs_cpy = malloc(qs.len + 1);
                memcpy(qs_cpy, qs.p, qs.len);
                qs_cpy[qs.len] = '\0';
                
                char *pair = strtok(qs_cpy, "&");
                while (pair != NULL) {
                    char *equal_sign = strchr(pair, '=');
                    if (equal_sign != NULL) {
                        *equal_sign = '\0';
                        
                        if (strcmp(pair, "name") == 0) {
                            name_value = equal_sign + 1;
                            break;
                        }
                    }
                    
                    pair = strtok(NULL, "&");
                }
                
                free(qs_cpy);
            }

            struct mg_str response_body = { .p = "<html><body>", .len = strlen("<html><body>") };
            if (name_value != NULL) {
                char body[256];
                snprintf(body, sizeof(body), "Name: %s", name_value);
                response_body.p = body;
                response_body.len = strlen(body);
            }
            
            const struct mg_str http_response =
                { .p = "<html><head><title>Result</title></head>"
                       "<body>" "<h1>", .len = sizeof("<html><head><title>Result</title></head>"
                                                      "<body>" "<h1>") - 1 };
            
            mg_printf(nc, "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html;\r\n"
                         "\r\n");
            mg_serve_http(nc, (struct http_message *) ev_data, &s_http_opts);
            mg_printf(nc, "%.*s%.*s</h1></body></html>\r\n",
                      (int) response_body.len, response_body.p,
                      (int) strlen(http_response.p + http_response.len),
                      http_response.p + http_response.len);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "0.0.0.0", 8080, handle_request);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    s_http_opts.document_root = ".";

    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on http://localhost:8080/\n");

    while (1) {
        mg_mgr_poll(&mgr, 100);
    }
}
