/* This C program extracts the contents of a zip file */
#include <stdio.h>
#include <stdlib.h> /* for exit() function */
#include <zip.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int err;
  struct zip_t *zip;

  if (argc != 2) {
    fprintf(stderr, "%s: usage: extract ZIPFILE\n", "extract");
    exit(EXIT_FAILURE);
  }

  zip = zip_open(argv[1], ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
  if (!zip) {
    fprintf(stderr, "%s: cannot open ZIPFILE %s\n", "extract", argv[1]);
    exit(EXIT_FAILURE);
  }

  err = zip_extract(zip, "/tmp/unpack", 0);
  if (err) {
    fprintf(stderr, "%s: cannot extract ZIPFILE %s\n", "extract", argv[1]);
    exit(EXIT_FAILURE);
  }

  zip_close(zip);

  return EXIT_SUCCESS;
}