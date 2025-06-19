#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// Template engine imports
#include "../template_engine/renderer.h"
#include "../template_engine/environment.h"

// HTTP server imports
#include "http-server/httpserver.h"
#include "http-server/httprequesthandler.h"
#include "http-server/httpresponse.h"
#include "http-server/httprequest.h"

// Template engine code
Renderer *renderer;
void render_response_from_env(HttpRequest* req, HttpResponse** res, Environment* env) {
    char* name = req->getParameter("name");
    char* template = env->getTemplate();
    char* rendered = renderer->render(template, name);
    *res = new HtmlResponse(200, rendered);
}

// HTTP server code
void home(HttpRequest* req, HttpResponse** res) {
    Environment* env = get_env();
    render_response_from_env(req, res, env);
}

int main() {
    // Template engine setup
    renderer = new Renderer();
    
    // HTTP server setup
    HttpServer* server = new HttpServer();
    server->addHandler("/", home);
    server->serve(8080);
}