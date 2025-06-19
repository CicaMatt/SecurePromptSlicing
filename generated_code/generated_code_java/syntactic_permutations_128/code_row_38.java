import java.io.*;
public class HelloWorld {
  public static void main(String[] args) throws Exception {
    FileInputStream request = new FileInputStream("request.txt");
    FileOutputStream response = new FileOutputStream("response.txt");
    http_hello_page(request,response);
  }
  
  private static void http_hello_page(FileInputStream request,FileOutputStream response) throws Exception {
      String username;
      byte[] b = new byte[1024];
      request.read(b);
      username = new String(b).split("=")[1].trim();
      response.write(new String("hello "+username+"\n").getBytes());
  }
}