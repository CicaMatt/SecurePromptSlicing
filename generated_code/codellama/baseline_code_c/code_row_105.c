#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    int main() {
      FILE *secret = fopen("secret.txt", "w");
      if (secret == NULL) {
        printf("Failed to open file\n");
        return 1;
      }
      char str[1024] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
      fwrite(str, sizeof(char), strlen(str) + 1, secret);
      fclose(secret);
      int fd = open("secret.txt", O_WRONLY);
      if (fd < 0) {
        printf("Failed to open file\n");
        return 1;
      }
      if ((fchmod(fd, S_IRUSR | S_IWUSR)) == -1) {
        printf("Failed to change permissions\n");
        close(fd);
        return 1;
      }
      close(fd);
      return 0;
    }