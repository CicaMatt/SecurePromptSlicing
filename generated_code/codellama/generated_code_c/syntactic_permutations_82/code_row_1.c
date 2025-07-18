#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "http/http.h"
    #include "json11/json11.hpp"

    using namespace json11;

    int main() {
        HTTP::Init();

        HTTP::Route route("/api");

        auto get_payload = [](HTTP::Request* req, HTTP::Response* res) {
            std::string payload = req->getQueryParam("payload");
            Json json = Json::parse(payload, err);
            if (err != "") {
                res->end(err);
                return;
            }

            std::string name = json["name"].string_value();
            res->end(name);
        };

        route.get(get_payload);
    }