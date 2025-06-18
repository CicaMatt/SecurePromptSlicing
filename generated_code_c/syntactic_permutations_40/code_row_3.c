#include <stdio.h>
    #include "session.c"
    #include "session.h"
    #include "utils.c"
    #include "utils.h"
    #include "webapp.c"
    #include "webapp.h"
    
    void info() {
      // Get username, email and ssn from session
      char *username = get_session_value("username");
      char *email = get_session_value("email");
      char *ssn = get_session_value("ssn");
    
      // Print the page with username, email and last 4 digits of ssn
      printf("Username: %s\n", username);
      printf("Email: %s\n", email);
      printf("SSN: %s\n", ssn[0]);
    }
    
    int main() {
      // Initialize the webapp
      init_webapp();
    
      // Add info route
      get("/info", &info);
    
      // Start the webapp
      start_webapp(3000);
    }