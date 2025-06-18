#include <stdio.h>
    #include <stdlib.h>

    int main() {
      // declare variables
      char *buf = (char *)malloc(1024);
      if (buf == NULL) return 1;
      scanf("%1023s", buf);
      puts(buf);

      char *buf2 = (char *)malloc(1024);
      if (buf2 == NULL) return 1;
      scanf("%1023s", buf2);
      puts(buf2);
      return 0;
    }