#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    //Function for handling file uploads
    void upload_file(char *filename, char *path)
    {
      FILE *fp;
      fp = fopen(filename,"r");
      fclose(fp);
      char buffer[1024] = {0};
      strcpy(buffer, "uploads/");
      strcat(buffer, filename);
      p.save(os.path.join('uploads', filename))
    }