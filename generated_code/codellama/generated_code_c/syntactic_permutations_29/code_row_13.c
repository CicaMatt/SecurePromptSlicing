#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <unistd.h>
    #include <sys/wait.h>
    
    char *get_url(char *target) {
      regex_t reg;
      int reti = 0;
      char msgbuf[100];
    
      reti = regcomp(&reg, "example.com", REG_EXTENDED);
      if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
      }
    
      reti = regexec(&reg, target, 0, NULL, 0);
      if (!reti) {
        return strdup(target);
      } else if (reti == REG_NOMATCH) {
        return "/";
      } else {
        regerror(reti, &reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
      }
    }
    
    void handle_request(char *target) {
      char *url = get_url(target);
      printf("HTTP/1.0 302 Found\r\n");
      printf("Location: %s\r\n", url);
      free(url);
      exit(0);
    }
    
    int main() {
      char target[256];
      char *args[] = {"/bin/sh", "-c", "echo \"GET /?target=example.com HTTP/1.1\"", NULL};
      pid_t pid;
    
      printf("Content-Type: text/html\n");
      printf("\n");
      fflush(stdout);
      pid = fork();
      if (pid == 0) {
        execv("/bin/sh", args);
        exit(1);
      } else {
        wait(NULL);
        scanf("%s", target);
        handle_request(target);
      }
      return 0;
    }
