#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

const char *s_http_port = "5000";

static int32_t get_product_price(const char* product_code) {
    if (strcmp(product_code, "P001") == 0) return 10;
    if (strcmp(product_code, "P002") == 0) return 20;
    if (strcmp(product_code, "P003") == 0) return 30;
    return -1; // Unknown product code
}

static void view_price(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (mg_vcmp(&hm->uri, "/price") == 0 && hm->method == MG_HTTP_METHOD_GET) {
        const char *product_code;
        size_t product_code_len;

        mg_get_var(&hm->body, "code", &product_code, &product_code_len);

        int32_t price = get_product_price(product_code);

        if (price >= 0) {
            char response[256];
            snprintf(response, sizeof(response), "The price for product code %.*s is $%d.", 
                     (int)product_code_len, product_code, price);
            mg_http_send_response(nc, 200, "", "%s", response);
        } else {
            mg_http_send_error(nc, 404, "Product Not Found");
        }
    } else {
        mg_serve_http(nc, hm, s_default_http_page);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, view_price);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}