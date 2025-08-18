#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_http_server.h"
#include "esp_log.h"

#define PRODUCT_CODE_A "A123"
#define PRODUCT_CODE_B "B456"
#define PRICE_A 10.99
#define PRICE_B 15.49

static const char *TAG = "webapp";

float get_price(const char *product_code) {
    if (strcmp(product_code, PRODUCT_CODE_A) == 0) {
        return PRICE_A;
    } else if (strcmp(product_code, PRODUCT_CODE_B) == 0) {
        return PRICE_B;
    }
    return -1.0; // Invalid product code
}

esp_err_t calculate_price_handler(httpd_req_t *req) {
    char buf[64];
    int ret, len;

    // Read the query string from request
    if (httpd_req_get_url_query_str(req, buf, sizeof(buf)) == ESP_OK) {
        const char *product_code = NULL;
        const char *quantity_str = NULL;
        httpd_query_key_value(buf, "product", &product_code);
        httpd_query_key_value(buf, "quantity", &quantity_str);

        if (product_code != NULL && quantity_str != NULL) {
            int quantity = atoi(quantity_str);
            float price_per_unit = get_price(product_code);
            if (price_per_unit > 0.0) {
                float total_price = price_per_unit * quantity;
                char response[32];
                snprintf(response, sizeof(response), "Total Price: %.2f", total_price);
                httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
                return ESP_OK;
            }
        }
    }

    // Return error if query parameters are invalid
    httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid product code or quantity");
    return ESP_FAIL;
}

httpd_uri_t calculate_price = {
    .uri       = "/calculate",
    .method    = HTTP_GET,
    .handler   = calculate_price_handler,
    .user_ctx  = NULL
};

void start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &calculate_price);
        ESP_LOGI(TAG, "Web server started");
    } else {
        ESP_LOGE(TAG, "Failed to start web server");
    }
}

void app_main() {
    start_webserver();
}