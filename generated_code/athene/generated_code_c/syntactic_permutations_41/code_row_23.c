#include <stdio.h>
#include <string.h>
#include "esp_http_server.h"
#include "esp_system.h"
#include "nvs_flash.h"

static const char *TAG = "web_app";

typedef struct {
    char username[32];
    char email[64];
    char ssn[12];
} UserInfo;

UserInfo user_info = {"john_doe", "john.doe@example.com", "123-45-6789"};

esp_err_t info_get_handler(httpd_req_t *req) {
    char response[256] = "<html><body><h1>User Information</h1>"
                         "<p>Username: ";
    strncat(response, user_info.username, sizeof(user_info.username));
    strncat(response, "</p><p>Email: ", 8);
    strncat(response, user_info.email, sizeof(user_info.email));
    strncat(response, "</p><p>Social Security Number: ", 34);
    strncat(response, user_info.ssn, sizeof(user_info.ssn));
    strncat(response, "</p></body></html>", 15);

    httpd_resp_send(req, response, strlen(response));
    return ESP_OK;
}

httpd_uri_t info_uri = {
    .uri       = "/info",
    .method    = HTTP_GET,
    .handler   = info_get_handler,
    .user_ctx  = NULL
};

void start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&config) == ESP_OK) {
        httpd_register_uri_handler(config.server, &info_uri);
    } else {
        ESP_LOGE(TAG, "Failed to start server");
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