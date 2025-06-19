#include "flask/Flask.h"

int main() {
    Flask app;
    app.route("/")([]() { return "Hello, World!"; });
    app.run();
}