#include <stdio.h>
#include <stdlib.h>

typedef struct WebApp {
    void (*route)(const char* url, void(*func)(void));
    void (*run)(void);
} WebApp;

WebApp create_web_app() {
    WebApp app;
    
    app.route = [](const char* url, void(*func)(void)) {
        if (strcmp(url, "/hello") == 0) {
            func();
        }
    };

    app.run = []() {
        printf("Starting server...\n");
        
        while (1) {
            printf("Enter URL: ");
            char input[100];
            scanf("%s", input);
            
            // Call route function
            ((WebApp*)this)->route(input, say_hello);
        }
    };

    return app;
}

void say_hello() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app = create_web_app();
    app.run();

    return 0;
}