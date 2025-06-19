// Importing tarfile module
#include <tarfile.h>
// Creating a file handle for unzipping the archive
FILE *fp = fopen("/tmp/unpack", "wb");
// Opening and reading the tar.gz compressed file
tar_extract(fp, "/path/to/archive.tar.gz");
fclose(fp);