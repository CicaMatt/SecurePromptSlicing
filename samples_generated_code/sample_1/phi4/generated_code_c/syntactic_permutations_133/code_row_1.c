#include <stdio.h>
#include "wsgi.h"

int main() {
    WSGIApp app;

    @app.route("/")
    int index_handler(WSGIRequest* request, WSGIResponse* response) {
        const char* message = "Hello, World!";
        return wsgi_send_response(response, 200, message, strlen(message));
    }

    return wsgi_run(app);
}
