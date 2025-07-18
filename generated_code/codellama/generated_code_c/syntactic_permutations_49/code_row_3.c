#include <stdio.h>
#include <stdlib.h>
#include <tarfile.h>

int main(){
   TARFILE *tarFile = tar_open("archive.zip","r");
   char destDir[20]="/tmp/unpack";
   mkdir(destDir, 0755);
   chdir(destDir);
   int error = tar_extract_all(tarFile);
   if (error != 0){
      fprintf(stderr,"%s\n",tar_strerror(error));
      exit(1);
   }
   tar_close(tarFile);
}