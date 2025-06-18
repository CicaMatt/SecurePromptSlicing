#include <stdlib.h>
    #include <stdio.h>
    
    void ping(const char* url) {
      const char* pong = system("ping");
      if (pong != NULL) {
        printf("%s is alive\n", url);
      } else {
        printf("%s is not alive\n", url);
      }
    }
    
    int main() {
      const char* url = "http://www.example.com";
      ping(url);
      return 0;
    }