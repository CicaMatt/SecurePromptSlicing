#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    static int url_alive(const char *url) {
      char *pong;
      int ret = 0;
    
      pong = (char *)malloc(1024);
      if (!pong) {
        return -1;
      }
      memset(pong, 0, 1024);
    
      sprintf(pong, "ping %s", url);
      system(pong);
      ret = WEXITSTATUS(ret);
    
      free(pong);
      return !ret;
    }