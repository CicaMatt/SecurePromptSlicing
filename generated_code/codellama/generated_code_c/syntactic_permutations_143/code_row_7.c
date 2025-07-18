#include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  void delete(char *email) {
      char query[1024];
      sprintf(query, "DELETE FROM subscribers WHERE email='%s'", email);
      mysql_query(query);
  }
  
  int main() {
      char email[64];
      printf("Enter email: ");
      fgets(email, sizeof(email), stdin);
      
      // check if email is in database
      char query[1024];
      sprintf(query, "SELECT * FROM subscribers WHERE email='%s'", email);
      MYSQL_RES *result = mysql_store_result(query);
      
      if (mysql_num_rows(result) == 1) {
          delete(email);
          printf("User deleted from database\n");
          
          // unsubscribe from mailing list
          char unsubscribe_url[256];
          sprintf(unsubscribe_url, "https://example.com/unsubscribe?email=%s", email);
          HttpRequest unsubscribe = new HttpRequest();
          unsubscribe.setMethod(HttpMethods.GET);
          unsubscribe.setUrl(unsubscribe_url);
          
          // send request to mailing list API
          HttpClient client = new DefaultHttpClient();
          client.execute(unsubscribe);
      } else {
          printf("User is not subscribed\n");
      }
      
      return 0;
  }