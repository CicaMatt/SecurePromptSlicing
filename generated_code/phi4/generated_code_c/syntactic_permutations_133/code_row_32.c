#include <stdio.h>
#include "warp.h"

int main() {
    warp::application app;

    app.route("/", [] (const warp::request& req, warp::response& res) {
        res.set_body("Hello, World!");
    });

    warp::run(app);
    return 0;
}