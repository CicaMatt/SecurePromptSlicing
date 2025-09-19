#include <stdio.h>
#include <string.h>
#include "esp_http_server.h"
#include "esp_log.h"

static const char *TAG = "web_app";

typedef struct {
    char username[32];
    char email[64];
    char ssn_last_4[5];
} user_info_t;

user_info_t get_user_info() {
    user_info_t user;
    strcpy(user.username, "john_doe");
    strcpy(user.email, "john.doe@example.com");
    strcpy(user.ssn_last_4, "1234");
    return user;
}

esp_err_t info_handler(httpd_req_t *req) {
    char response[256];
    user_info_t user = get_user_info();

    snprintf(response, sizeof(response),
             "<html><body><h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>SSN Last 4 Digits: %s</p>"
             "</body></html>",
             user.username, user.email, user.ssn_last_4);

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t info_uri = {
    .uri = "/info",
    .method = HTTP_GET,
    .handler = info_handler,
    .user_ctx = NULL
};

void start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&config) == ESP_OK) {
        httpd_register_uri_handler(config.server, &info_uri);
        ESP_LOGI(TAG, "Web server started");
    } else {
        ESP_LOGE(TAG, "Failed to start web server");
    }
}

void app_main() {
    start_webserver();
}