#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <assert.h>
    #include "httpServer.h"
    #define MAX_BUF 1024
    typedef struct {
        char username[50];
        char email[100];
        int SSN;
    } sessionData;
    void info(httpRequest *req, httpResponse *res) {
      // Get the session data
      sessionData* sd = (sessionData*) getSessionData(req);
      assert(sd != NULL);
  
      // Setup response content type and body
      char buf[MAX_BUF];
      sprintf(buf, "Username: %s\nEmail: %s\nSSN: %d", sd->username, sd->email, sd->SSN);
      setContentType(res, "text/plain");
      setBody(res, buf);
    }
    int main() {
      // Create a new web server that listens on port 8080
      httpServer *svr = createHttpServer(8080);
  
      // Add a single route for the root path '/' and the GET method
      addRoute(svr, "/info", GET, info);
      
      // Setup session data. We only have three variables to store
      setSessionDataSize(svr, sizeof(sessionData));
  
      // Run the web server forever
      runHttpServer(svr);
  
      return 0;
    }