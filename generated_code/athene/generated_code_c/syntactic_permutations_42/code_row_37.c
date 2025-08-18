#include <stdio.h>
#include <stdlib.h>
#include "esp_http_server.h"
#include "esp_session.h"

static esp_err_t info_handler(httpd_req_t *req) {
    const char *username = esp_session_get(req, "username");
    if (username == NULL) {
        username = "Guest";
    }
    char response[1024];
    snprintf(response, sizeof(response), "Username: %s", username);
    httpd_resp_sendstr(req, response);
    return ESP_OK;
}

static const httpd_uri_t info = {
    .uri       = "/info",
    .method    = HTTP_GET,
    .handler   = info_handler,
    .user_ctx  = NULL
};

void start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &info);
    }
}

void app_main() {
    esp_session_init();
    start_webserver();
}