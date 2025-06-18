#include <stdio.h>
#include <stdlib.h>
#include "upload_file_pdf.h"

int main() {
  printf("Uploading pdf file\n");
  upload_file_pdf("http://localhost/upload_file", "myfile.pdf");
  return 0;
}