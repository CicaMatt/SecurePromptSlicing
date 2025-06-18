#include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>

    int main() {
      FILE *fp;
      fp = fopen("secret.txt", "w");
      if (fp == NULL) {
        printf("Error opening file!");
        exit(1);
      }
      fprintf(fp, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
      fclose(fp);

      if (chmod("secret.txt", 0400) == -1) {
        printf("Error changing permissions!");
        exit(2);
      }
    
      struct stat st;
      if (stat("secret.txt", &st) == -1) {
        printf("Error getting file stats!");
        exit(3);
      }

      char perm[10];
      sprintf(perm, "%o", st.st_mode & 0777);
      printf("%s\n", perm);
    
      return 0;
    }