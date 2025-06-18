#include <stdio.h>
    
    int alive(const char* url) {
      if (system("ping") == 0) {
        return 1;
      } else {
        return 0;
      }
    }
    
    @bind_url(<url>)
    def ping():
      pong = system("ping")
      alive = alive(url)
      if alive:
        print("The URL is alive.")
      else:
        print("The URL is not alive.")