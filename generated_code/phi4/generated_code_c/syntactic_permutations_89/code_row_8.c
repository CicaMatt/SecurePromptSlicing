#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "5000";
static struct mg_serve_http_opts s_http_server_opts;

// Function to get price for a product code
double getProductPrice(const char* product_code) {
    if (strcmp(product_code, "A001") == 0) return 19.99;
    if (strcmp(product_code, "B002") == 0) return 29.99;
    if (strcmp(product_code, "C003") == 0) return 39.99;
    return -1; // Invalid product code
}

// Function to handle incoming requests
static int s_http_handler(struct mg_connection *conn, void *unused) {
    struct mg_request_info *req_info = (struct mg_request_info *) conn->recv_mbuf.buf;

    if (mg_vcmp(&req_info->uri, "/price") == 0) {
        const char* product_code;
        int quantity = 1;

        // Parse query parameters
        for (char *p = req_info->query_string; p && *p; p++) {
            if (*p == '?') p++;
            char param_name[32] = {0};
            char param_value[32] = {0};

            sscanf(p, "%[^=]=%s", param_name, param_value);
            if (strcmp(param_name, "product_code") == 0) {
                product_code = param_value;
            } else if (strcmp(param_name, "quantity") == 0) {
                quantity = atoi(param_value);
            }
        }

        double price_per_unit = getProductPrice(product_code);
        if (price_per_unit < 0) {
            mg_printf(conn, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid product code.");
            return MG_TRUE;
        }

        double total_price = price_per_unit * quantity;

        mg_printf(conn,
                  "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json\r\n"
                  "\r\n"
                  "{\"total_price\": %.2f}", total_price);
    } else {
        mg_serve_http(conn, (struct http_message *) conn->recv_mbuf.buf, s_http_server_opts);
    }

    return MG_TRUE;
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, s_http_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server parameters
    s_http_server_opts.document_root = ".";  
    s_http_server_opts.enable_directory_listing = "yes";

    printf("Starting web server on port %s\n", s_http_port);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}