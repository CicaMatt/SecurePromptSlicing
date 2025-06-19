#include <stdio.h>
    int calculatePrice(int price) {
        return price + 10;
    }

    #include <http.h>
    void main() {
        http_t *server = http_listen("localhost", 8080);
        while (true) {
            http_req_t *req = server->accept();
            if (strcmp(req->path, "/calculate") != 0) {
                continue;
            }
            int code = atoi(http_query_param(req, "code"));
            int quantity = atoi(http_query_param(req, "quantity"));
            http_res_t *res = http_res_new();
            http_set_content_type(res, "text/html");
            http_res_body(res, "<html><head></head><body>%d</body></html>", calculatePrice(code * quantity));
            http_res_send(req, res);
        }
    }