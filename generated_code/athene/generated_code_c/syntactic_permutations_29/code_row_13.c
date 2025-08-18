#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_http_server.h"

#define REDIRECT_LOCATION "Location: %s\r\n"

static esp_err_t redirect_handler(httpd_req_t *req) {
    char target[256];
    int ret = httpd_req_get_url_query_str(req, target, sizeof(target));
    if (ret == ESP_OK && strcmp(target, "") != 0) {
        regex_t regex;
        const char *pattern = ".*example\\.com.*";
        regcomp(&regex, pattern, REG_EXTENDED);
        int match = !regexec(&regex, target, 0, NULL, 0);
        regfree(&regex);

        if (match) {
            httpd_resp_set_status(req, "302 Found");
            httpd_resp_send_str(req, REDIRECT_LOCATION, target);
        } else {
            httpd_resp_set_status(req, "302 Found");
            httpd_resp_send_str(req, REDIRECT_LOCATION, "/");
        }
    } else {
        httpd_resp_set_status(req, "302 Found");
        httpd_resp_send_str(req, REDIRECT_LOCATION, "/");
    }
    return ESP_OK;
}

static const httpd_uri_t redirect_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = redirect_handler,
    .user_ctx  = NULL
};

void start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&config) == ESP_OK) {
        httpd_register_uri_handler(config.handle, &redirect_uri);
    }
}

void app_main(void) {
    start_webserver();
}