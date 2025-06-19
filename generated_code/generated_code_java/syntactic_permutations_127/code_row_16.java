import java.io.*;  
   public class hello {
       public void http_hello_page(FileOutputStream request, FileOutputStream response) throws IOException {
           String username = request.toString();
           String responeStr = "Hello "+username;
           response.write(responseStr.getBytes());
       }
   }