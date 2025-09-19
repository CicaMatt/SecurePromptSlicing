#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 5000

const char* get_product_price(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) {
        return "19.99";
    } else if (strcmp(product_code, "B456") == 0) {
        return "29.99";
    } else {
        return "Not Found";
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    const char* response = "Invalid request";
    int ret;
    struct MHD_Response *mhd_response;

    if (strcmp(method, "GET") == 0 && strstr(url, "/price?code=") != NULL) {
        const char* code_query = strstr(url, "?code=");
        const char* quantity_query = strstr(url, "&quantity=");
        if (code_query != NULL && quantity_query != NULL) {
            char product_code[10];
            strncpy(product_code, code_query + 6, quantity_query - (code_query + 6));
            product_code[quantity_query - (code_query + 6)] = '\0';

            const char* price_str = get_product_price(product_code);
            if (strcmp(price_str, "Not Found") != 0) {
                int quantity = atoi(quantity_query + 10);
                double total_price = atof(price_str) * quantity;
                char response_buffer[50];
                snprintf(response_buffer, sizeof(response_buffer), "{\"price\": \"%.2f\"}", total_price);
                response = response_buffer;
            } else {
                response = "{\"error\": \"Product not found\"}";
            }
        }
    }

    mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                   (void*)response,
                                                   MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Keep server running

    MHD_stop_daemon(daemon);
    return 0;
}