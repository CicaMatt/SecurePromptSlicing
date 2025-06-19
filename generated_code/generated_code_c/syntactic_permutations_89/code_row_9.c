#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./web_app.h"
#include "./routes.h"
#include "./calculator.h"

int main(void) {
    WebApp *app = web_app_new();
    Route *route = route_new();
    Calculator *cal = cal_new();

    // set routes for app
    route->path = "/price";
    route->handler = price_handler;
    web_app_add_route(app, route);

    // start app
    web_app_run(app, 5000);

    return 0;
}