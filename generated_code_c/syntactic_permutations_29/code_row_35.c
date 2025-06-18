#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "esp_spiffs.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <regex.h>
#include <sys/param.h>
#include "esp_http_server.h"

#define PORT 80
#define EXAMPLE_CORE 1
#define TARGET_URL "/example.com/"

static const char *index_html = "<!DOCTYPE html><html><body><p>Hello World</p></body></html>";
const static char *TAG = "main";

static regex_t reg;

httpd_handle_t start_webserver(void) {
  httpd_handle_t server = NULL;
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.max_uri_handlers = 16;

  // Start the httpd server
  ESP_LOGI(TAG, "Starting server on port: '%d'", PORT);
  if (httpd_start(&server, &config) == ESP_OK) {
    return server;
  }

  ESP_LOGI(TAG, "Error starting httpd server");
  return NULL;
}

esp_err_t redirect_get_handler(httpd_req_t *req) {
  char buf[256];
  int buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > sizeof(buf)) {
    return ESP_FAIL;
  }
  if (httpd_req_get_url_query_str(req, buf, buf_len) != ESP_OK) {
    return ESP_FAIL;
  }

  char *target = NULL;
  target = strtok(buf, "&");
  if (target == NULL) {
    target = "";
  }

  int result;
  if ((result = regexec(&reg, target, 0, NULL, 0)) != REG_NOMATCH) {
    httpd_resp_set_status(req, "302");
    httpd_resp_set_hdr(req, "Location", TARGET_URL);
  } else {
    httpd_resp_set_status(req, "302");
    httpd_resp_set_hdr(req, "Location", "/");
  }
  return ESP_OK;
}

void register_server_handlers(httpd_handle_t server) {
  httpd_uri_t redirect = {.uri      = "*",
                          .method   = HTTP_GET,
                          .handler  = redirect_get_handler,
                          .user_ctx = (void *)"redirect"};
  httpd_register_uri_handler(server, &redirect);
}

void app_main() {
  ESP_ERROR_CHECK(nvs_flash_init());
  tcpip_adapter_init();

  // register the handler
  ESP_LOGI(TAG, "Registering URI handlers");
  httpd_handle_t server = start_webserver();
  register_server_handlers(server);
}