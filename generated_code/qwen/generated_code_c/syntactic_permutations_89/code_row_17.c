#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

static int get_price(const char *product_code) {
    if (strcmp(product_code, "A1") == 0) return 10;
    else if (strcmp(product_code, "B2") == 0) return 20;
    else if (strcmp(product_code, "C3") == 0) return 30;
    return -1; // Product not found
}

static int calculate_total_price(const char *product_code, int quantity) {
    int price = get_price(product_code);
    if (price == -1) return -1; // Error: product not found
    return price * quantity;
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                               const char *url, const char *method,
                               const char *version, const char *upload_data,
                               size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int total_price = -1;
    if (strstr(url, "/price?")) {
        const char *product_code = strstr(url, "product=");
        const char *quantity_str = strstr(url, "&quantity=");
        
        if (product_code && quantity_str) {
            product_code += 8; // Move past "product="
            quantity_str += 10; // Move past "&quantity="

            int quantity = atoi(quantity_str);
            total_price = calculate_total_price(product_code, quantity);
        }
    }

    char response[50];
    if (total_price != -1) {
        sprintf(response, "{\"total_price\": %d}", total_price);
    } else {
        strcpy(response, "{\"error\": \"Invalid product code or quantity\"}");
    }

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response), 
                                                                         (void*) response, 
                                                                         MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}