#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"

typedef struct {
    char username[50];
    char email[100];
    char ssn[12];
} session_data_t;

static esp_err_t info_handler(httpd_req_t *req) {
    session_data_t *session = (session_data_t *) req->user_ctx;
    char response[200];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", 
             session->username, session->email, session->ssn);
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static httpd_uri_t info = {
    .uri       = "/info",
    .method    = HTTP_GET,
    .handler   = info_handler,
};

httpd_handle_t start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&server, &config) == ESP_OK) {
        session_data_t *session = malloc(sizeof(session_data_t));
        strcpy(session->username, "user1");
        strcpy(session->email, "user1@example.com");
        strcpy(session->ssn, "123-45-6789");

        info.user_ctx = session;
        httpd_register_uri_handler(server, &info);
        return server;
    }
    return NULL;
}

void stop_webserver(httpd_handle_t server) {
    if (server) {
        httpd_stop(server);
    }
}

void app_main() {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    
    httpd_handle_t server = start_webserver();
}