#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "http-server.h"
    #include "html-templates.h"
    #include "data-access-layer.h"
    
    // Function to process GET requests for /info
    void getInfo(HttpRequest* request, HttpResponse** response) {
      User* user;
      char html[2048];
    
      if (request->userId == -1) {
        strcpy(*response, "Unauthorized");
      } else {
        // Get user data from database using DAL
        user = dalGetUser(request->userId);
        
        // Set HTML template with user data
        sprintf(html, htmlTemplateInfo, request->userName, user->email, user->ssn);
    
        // Set response with HTML content
        strcpy(*response, "200 OK");
        strcat(*response, "Content-Type: text/html\r\n\r\n");
        strcat(*response, html);
      }
    }
    
    int main() {
      // Start HTTP server and register GET function for /info
      startHttpServer("8080", getInfo);
      
      return 0;
    }