#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <assert.h>
    #include "request.h"
    #include "response.h"
    
    void redirect(Request *req, Response *res, char *target) {
      char *newTarget = malloc(strlen(target) + 2);
      strcpy(newTarget, target);
      newTarget[0] = '/';
      res->headers["Location"] = newTarget;
      res->statusCode = 302;
    }
    
    void routeHandler(Request *req, Response *res) {
      char *target = req->query["target"];
      if (strstr(target, "example.com") != NULL) {
        redirect(req, res, target);
      } else {
        redirect(req, res, "/");
      }
    }
    
    int main() {
      startServer("8080", routeHandler);
      return 0;
    }