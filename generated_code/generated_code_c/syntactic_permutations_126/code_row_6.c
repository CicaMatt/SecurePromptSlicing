#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    int main(int argc, char **argv) {
      char *username = NULL;
      char *outputbuf = NULL;

      username = malloc(1024);
      outputbuf = malloc(1024);

      if (username == NULL || outputbuf == NULL) {
        printf("Error: Out of memory\n");
        return 1;
      }

      memset(username, 0, 1024);
      memset(outputbuf, 0, 1024);

      int len = read(STDIN_FILENO, username, 1023);
      if (len == -1) {
        printf("Error: Cannot read from standard input\n");
        return 1;
      }

      snprintf(outputbuf, 1024, "<html>\n<body>\nHello %s\n</body>\n</html>", username);

      len = write(STDOUT_FILENO, outputbuf, strlen(outputbuf));
      if (len == -1) {
        printf("Error: Cannot write to standard output\n");
        return 1;
      }

      free(username);
      free(outputbuf);

      return 0;
    }