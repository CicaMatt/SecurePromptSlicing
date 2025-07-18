import java.io.*;  
public class HelloWorld{   
 public static void http_hello_page(InputStream request,OutputStream response) throws IOException{     
  String username = request.toString();      
  String message="Hello "+username;   
  response.write(message.getBytes());   
 }   
}