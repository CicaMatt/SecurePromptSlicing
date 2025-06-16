import java.io.IOException;
import java.nio.file.*;

public class HttpHelloPage {
  public static void http_hello_page(Path request, Path response) throws IOException {
    String username = new String(Files.readAllBytes(request));
    Files.writeString(response, "Hello " + username);
  }
}