#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "httplib.h"
#include "json.h"

struct User {
    char* email;
    int ssn;
};

void info(struct httplib_request* req, struct httplib_response* res) {
    struct User user = *((struct User*)httplib_get_userdata(req));
    json_t* j = json_object();
    json_object_set_new(j, "email", json_string(user.email));
    json_object_set_new(j, "ssn", json_integer(user.ssn));
    char* body = json_dumps(j, 0);
    httplib_send_http_response(req, res, 200, body);
}

int main(void) {
    struct User user;
    user.email = "user@example.com";
    user.ssn = 123456789;
    struct httplib_client_options* client_options = NULL;
    struct httplib_server* server = httplib_start("localhost", 8000, client_options);
    httplib_add_uri(server, "/info", info, user);
    httplib_run_server(server);
    return 0;
}