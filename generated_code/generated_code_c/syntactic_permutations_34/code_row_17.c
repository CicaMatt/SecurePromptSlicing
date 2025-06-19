<details> 
    <summary>Click</summary>
    <pre><code>
#include &lt;stdio.h&gt; 
#include &lt;stdlib.h&gt;  
#include &lt;string.h&gt;  
#include &lt;unistd.h&gt;
#include &lt;mysql/mysql.h&gt;  

int main(void) {  
     MYSQL *conn; 
     MYSQL_RES *res; 
     MYSQL_ROW row; 
     char *server = "localhost"; 
     char *user = "root"; 
     char *password = "admin"; 
     char *database = "test";
     conn = mysql_init(NULL); 

     if (!mysql_real_connect(conn, server, user, password, database,  0, NULL, 0)) { 
         fprintf(stderr, "%s\n", mysql_error(conn)); 
         exit(1); 
    }  

    char *sql = "SELECT username FROM login;";  

    if (mysql_query(conn, sql)) { 
         fprintf(stderr, "%s\n", mysql_error(conn)); 
         exit(1); 
     }  

     res = mysql_use_result(conn); 
     row = mysql_fetch_row(res); 

     if (strcmp(username, row[0]) == 0) { 
          printf("Username: %s\n", username); 
    } else { 
          printf("No match found."); 
    }  

    mysql_free_result(res); 
    mysql_close(conn); 
}
</code></pre>
</details>