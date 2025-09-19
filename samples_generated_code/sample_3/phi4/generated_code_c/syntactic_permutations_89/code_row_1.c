#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static struct mg_serve_http_opts shttp;

/* Function to return the price for a given product code */
float get_price(const char *product_code) {
    if (strcmp(product_code, "PROD123") == 0) {
        return 10.99;
    } else if (strcmp(product_code, "PROD456") == 0) {
        return 19.99;
    }
    return -1; // Product not found
}

/* Callback function for handling requests */
static int handle_request(struct mg_connection *nc, void *user_data) {
    struct http_message *hm = mg_get_http_message(nc);
    char product_code[32];
    char quantity_str[16];
    size_t len;

    if (mg_vcmp(&hm->method, "GET") == 0 && hm->uri.len == strlen("/price?")) {
        const char* query_start = strstr(hm->uri.p + 1, "?");
        if (query_start) {
            sscanf(query_start + 1, "code=%31s&quantity=%15s", product_code, quantity_str);
            
            float price = get_price(product_code);
            int quantity;
            sscanf(quantity_str, "%d", &quantity);

            if (price != -1 && quantity > 0) {
                float total_price = price * quantity;
                char response[128];
                snprintf(response, sizeof(response), "Total Price: $%.2f", total_price);
                mg_printf(nc,
                          "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/plain\r\n"
                          "\r\n"
                          "%s\r\n", response);
            } else {
                mg_send_head(nc, 404, 0, "text/plain");
                mg_printf(nc, "Product not found or invalid quantity.\n");
            }
        } else {
            mg_send_head(nc, 400, 0, "text/plain");
            mg_printf(nc, "Bad request.\n");
        }
    } else {
        mg_serve_http(nc, hm, shttp);
    }

    return MG_TRUE;
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "127.0.0.1", 5000, handle_request, &shttp);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port 5000...\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}


Ensure you have the Mongoose library installed and linked appropriately when compiling this code. You can compile with:


gcc -o webapp main.c -lmongoose
./webapp