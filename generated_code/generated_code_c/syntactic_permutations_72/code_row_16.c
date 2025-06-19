#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

void upload_(const char *name, const char *file_content) {
  // Create the uploads folder if it doesn't already exist.
  DIR* dir = opendir("uploads");
  if (dir) {
    closedir(dir);
  } else {
    mkdir("uploads", 0755);
  }

  // Save the file to the uploads folder with the specified name.
  FILE *fp = fopen(name, "wb");
  if (fp != NULL) {
    fwrite(file_content, 1, strlen(file_content), fp);
    fclose(fp);
  }
}