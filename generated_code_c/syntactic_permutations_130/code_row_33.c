#include <stdio.h>
 #include <stdlib.h>
 #include "render_response_from_env.h"

 #define RESPONSE_CODE 200
 #define HEADER_CONTENT_TYPE "Content-Type: text/html; charset=UTF-8"
 #define HEADER_SERVER "Server: MyWebServer"

 struct response {
     int status_code;
     const char *headers[2];
     const char *body;
 };

 struct environment {
     struct request *req;
     struct template *tmpl;
 };

 struct request {
     const char *name;
 };

 struct template {
     const char *html;
 };

 struct response render_response_from_env(struct environment env) {
     int status_code = RESPONSE_CODE;
     const char *headers[] = {HEADER_CONTENT_TYPE, HEADER_SERVER};
     const char *body = env.tmpl->html;

     struct response res = {status_code, headers, body};
     return res;
 }

 struct response home(struct environment env) {
     struct request req = {env.req->name};
     struct template tmpl = {env.tmpl->html};
     struct environment new_env = {&req, &tmpl};
     struct response res = render_response_from_env(new_env);

     return res;
 }