import java.io.*;

public class HelloWorld {
  public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
    String username = "";
    int character;
    while ((character = request.read()) != -1) {
      if (Character.isAlphabetic((char) character)) {
        username += (char) character;
      } else if (!username.isEmpty()) {
        break;
      }
    }
    
    String greeting = "Hello " + username + "\n";
    response.write(greeting.getBytes());
  }
}