#include <stdio.h>
#include <stdlib.h>
#include "httplib.h"
 
int main() {
  struct httplib_server *server = (struct httplib_server *) calloc(1, sizeof(*server));
  int ret;
  
  if (!server) {
    fprintf(stderr, "[ERROR] Failed to create server: out of memory");
    exit(EXIT_FAILURE);
  }
 
  httplib_set_post_handler(server, "/upload", upload_file);
 
  ret = httplib_start(server, NULL, port, NULL);
  if (ret != 0) {
    fprintf(stderr, "[ERROR] Failed to start server: %s", httplib_error_string(ret));
    exit(EXIT_FAILURE);
  }
 
  printf("Server started on port %d\n", port);
  printf("Press enter to stop the server and exit");
  getchar();
 
  httplib_stop(server);
  free(server);
 
  return EXIT_SUCCESS;
}