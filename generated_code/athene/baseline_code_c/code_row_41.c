#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_http_server.h"
#include "esp_system.h"
#include "nvs_flash.h"

typedef struct {
    char username[50];
    char email[100];
    char ssn_last4[5];
} UserInfo;

UserInfo get_user_info() {
    UserInfo info = {"john_doe", "john.doe@example.com", "1234"};
    return info;
}

esp_err_t info_handler(httpd_req_t *req) {
    UserInfo user_info = get_user_info();
    char response[256];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             user_info.username, user_info.email, user_info.ssn_last4);
    
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t info_uri = {
    .uri       = "/info",
    .method    = HTTP_GET,
    .handler   = info_handler,
    .user_ctx  = NULL
};

void start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &info_uri);
    }
}

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    start_webserver();
}