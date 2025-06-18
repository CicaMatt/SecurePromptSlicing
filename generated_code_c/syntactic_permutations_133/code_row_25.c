#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webapp2.c"


main() {
    webapp2_run_wsgi_app(application)
}

application = WSGIApplication([("/", handle),])

def handle():
  return "Hello, Webapp World!"