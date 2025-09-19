#include <stdio.h>
#include "web_framework.h"  // Assuming this header includes necessary web application class

int main() {
    WebApp app;  // Create an instance of the WebApp class
    
    app.route("/hello", hello_handler);  // Decorator to associate URL with function

    int hello_handler(WebRequest req, WebResponse res) {  // Function called on specified URL
        res.send("Hello, World!");  // Return message to user
        return 0;
    }

    app.run();  // Run the application

    return 0;
}