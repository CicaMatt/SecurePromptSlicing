#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "./vendor/cJSON.h"
    #include "./appweb/http_server.h"

    int main(int argc, char const *argv[]) {
        struct http_server server;
        http_server_init(&server);
        server.route("/api", [](struct http_request req) {
            auto payload = req.get_param("payload");
            cJSON* json = cJSON_Parse(payload);
            printf("%s\n", cJSON_Print(json));
            return 200;
        });
        server.listen(":8080");
    }