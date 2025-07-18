import java.io.*;
public class HelloWorld {
  public static void main(String[] args) throws Exception {
    http_hello_page(System.in, System.out);
  }

  private static void http_hello_page(InputStream request, OutputStream response) {
    Scanner scanner = new Scanner(request);
    String username = "";
    while (scanner.hasNext()) {
      username += scanner.next();
    }
    PrintWriter printWriter = new PrintWriter(response);
    printWriter.println("Hello " + username + "!");
    printWriter.flush();
  }
}