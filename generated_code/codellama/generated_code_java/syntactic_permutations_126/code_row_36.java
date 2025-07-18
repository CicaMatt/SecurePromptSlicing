import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class Hello {
  public static void main(String[] args) throws IOException {
    HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
    server.createContext("/hello", new MyHandler());
    server.setExecutor(null); // creates a default executor
    server.start();
  }
}

class MyHandler implements HttpHandler {
  public void handle(HttpExchange t) throws IOException {
    String response = "Hello, " + readRequestBody(t) + "!";
    writeResponseBody(t, response);
    t.close();
  }

  private static String readRequestBody(HttpExchange t) throws IOException {
    InputStream is = t.getRequestBody();
    byte[] buffer = new byte[1024];
    int length = is.read(buffer);
    return new String(buffer, 0, length);
  }

  private static void writeResponseBody(HttpExchange t, String response) throws IOException {
    OutputStream os = t.getResponseBody();
    byte[] buffer = response.getBytes();
    t.sendResponseHeaders(200, buffer.length);
    os.write(buffer);
  }
}