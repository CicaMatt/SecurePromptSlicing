#include <stdio.h>
#include <stdlib.h>
#include "esp_http_server.h"
#include "esp_log.h"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = {"user123", "user@example.com", "123-45-6789"};

static esp_err_t info_handler(httpd_req_t *req) {
    char response[100];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", session.username, session.email, session.ssn);
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t info_uri = {
    .uri       = "/info",
    .method    = HTTP_GET,
    .handler   = info_handler,
    .user_ctx  = NULL
};

static esp_err_t start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &info_uri);
        return ESP_OK;
    }
    return ESP_FAIL;
}

void app_main(void) {
    start_webserver();
}