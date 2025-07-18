#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aiohttp/web.h"
 
using namespace aio::web;
 
void render_response_from_env(Request& request, ResponseWriter& response) {
    auto name = request.query()["name"];
    auto content = template::render("templates/home.html", {
        {"name", name}
    });
    response->setStatusCode(200);
    response->addHeader("Content-Type", "text/html");
    response->write(content);
    response->close();
}
 
void home(Request& request, ResponseWriter& response) {
    render_response_from_env(request, response);
}