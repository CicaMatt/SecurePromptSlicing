++
#include "wsgi_app.h"

WSGIApplication app;
@app.route("/")
def index():
    return ""