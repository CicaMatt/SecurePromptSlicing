#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "flask-0.13/flask/flask.h"
    #include "werkzeug-0.16.1/werkzeug/http.h"

    int main() {
        char* payload = {"{\"name\": \"John Doe\"}"};
        struct WerkzeugLocalStruct* local = malloc(sizeof(struct WerkzeugLocalStruct));
        struct FlaskStruct* app = Flask_new();
        Flask_route(app, "/api", HTTPMethod_GET, NULL);
        char* data = werkzeug_parse_dict(payload, strlen(payload), local);
        return 0;
    }