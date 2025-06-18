//include header files for http
#include <httpd.h>
#include <apr_tables.h>
#include <apr_dbm.h>
#include <mod_dbd.h>
#include <apr_strings.h>

//define the main function
void post(request_rec *r) {
  //get the request parameters
  const char* user = apr_table_get(r->headers_in, "username");
  const char* message = apr_table_get(r->headers_in, "message");
  
  //call insert_user_message_in_db() function to insert the message in the database
  insert_user_message_in_db(r, user, message);
  
  //redirect the user to the main page
  const char* redirect = "/";
  apr_table_set(r->headers_out, "Location", redirect);
}