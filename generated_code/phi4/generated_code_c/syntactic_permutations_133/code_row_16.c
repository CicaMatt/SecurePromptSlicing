#include <stdio.h>
#include <stdlib.h>
#include "webapp.h"  // Assuming webapp.h contains the necessary WSGI application class definitions

int main() {
    WebApp app;  // Instance of the WebApp class as our WSGI application

    app.route("/hello", hello);  // Route URL "/hello" to the function hello

    return app.run();  // Run the web application
}

void hello(WebRequest req, WebResponse res) {  // Function called when user visits "/hello"
    res.send("Hello, World!");  // Return message to the user
}