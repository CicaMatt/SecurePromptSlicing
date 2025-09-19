#include <stdio.h>
#include "webapp_class.h" // Assuming a hypothetical header for web application class

int main() {
    WebApp app;
    
    app.route("/hello", handle_hello);

    if (app.run()) { // Hypothetical run method, returns 0 on success
        return 0;
    }
    return 1;
}

void handle_hello() {
    printf("Hello, World!\n");
}
