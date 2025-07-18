import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class HelloName {
  public static void main(String[] args) throws FileNotFoundException {
    PrintWriter response = new PrintWriter("response");
    try (FileInputStream requestStream = new FileInputStream(new File("request"))) {
      String username = "";
      int c;
      while ((c = requestStream.read()) != -1 && c != '\n') {
        username += (char) c;
      }
      response.println("Hello " + username);
    }
  }
}