#include <stdio.h>
    #include <stdlib.h> // for exit()
    #include <string.h> // for strcpy()
    
    #include "http.h" // for http_serve_file()
    #include "mime.h" // for get_mime_type() and get_mime_str()
    
    void img(request *req, response *res) {
      char file[128];
      strcpy(file, "images/");
      strcat(file, req->params.name); // copy the parameter into file
    
      http_serve_file(req, res, file); // serve the image
    }