#include <stdio.h>

typedef struct {
    int (*route)(char*, void(*)(void));
} Flask;

void hello() {
    printf("Hello, World!");
}

int main() {
    Flask app = (Flask){ .route = NULL };
    app.route("/", hello);
    // Simulate running the app
    hello();
    return 0;
}