#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "http_request.h"
#include "http_response.h"
#include "request.h"
#include "router.h"
#include "server.h"
#include "utils.h"
#include "webapplication.h"

int main(void) {
    router* r = router_new();
    route* redirect = route_redirect("/<url>", &redirect_invalid_url);
    router_add_route(r, redirect);

    webapplication* app = webapplication_new(r);
    server* srv = server_new(&app->base, 3000);
    server_run(srv);

    return 0;
}