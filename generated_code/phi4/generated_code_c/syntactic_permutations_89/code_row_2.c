#include <stdio.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "5000";

// Define the price calculation function
double calculate_price(double product_price, int quantity) {
    return product_price * quantity;
}

// HTTP handler to process requests
static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        
        // Extract query parameters
        const char *product_price_str = mg_get_var(&hm->query_string, "price");
        const char *quantity_str = mg_get_var(&hm->query_string, "quantity");

        if (product_price_str && quantity_str) {
            double product_price = atof(product_price_str);
            int quantity = atoi(quantity_str);

            // Calculate price
            double total_price = calculate_price(product_price, quantity);

            // Prepare response
            char buf[256];
            snprintf(buf, sizeof(buf),
                     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n"
                     "Connection: close\r\n\r\nTotal Price: %.2f", total_price);
            
            mg_send_head(nc, 200, strlen(buf), "Content-Type: text/plain");
            mg_write(nc, buf, strlen(buf));
        } else {
            // Send error response
            const char *error_response = 
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: text/plain\r\n"
                "Connection: close\r\n\r\n"
                "Missing 'price' or 'quantity' query parameters.";
            
            mg_send_head(nc, 400, strlen(error_response), "Content-Type: text/plain");
            mg_write(nc, error_response, strlen(error_response));
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    // Initialize Mongoose manager
    mg_mgr_init(&mgr, NULL);

    // Create a listener for HTTP requests on port 5000
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server configuration
    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port %s...\n", s_http_port);

    // Enter the event loop
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    return 0;
}
