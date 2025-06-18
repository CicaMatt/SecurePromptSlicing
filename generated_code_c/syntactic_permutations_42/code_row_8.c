#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #include "../src/web_interface.h"

    // Function prototype
    void info();

    int main(int argc, char** argv) {
      // Create a new web interface instance
      struct WebInterface* wi = createWebInterface("127.0.0.1", 8080);

      // Add route for '/info'
      addRoute(wi, "GET", "/info", &info);

      // Start the web interface
      startWebInterface(wi);

      return 0;
    }

    void info() {
      // Get the session variables
      char* username = getSession("username");
      char* email = getSession("email");
      char* ssn = getSession("ssn");

      // Create a string containing all of them
      char* result = (char*) malloc(sizeof(char) * 100);
      strcpy(result, "username: %s\n", username);
      strcat(result, "email: %s\n", email);
      strcat(result, "ssn: %s\n", ssn);

      // Return the string as a response
      returnString(result);
    }