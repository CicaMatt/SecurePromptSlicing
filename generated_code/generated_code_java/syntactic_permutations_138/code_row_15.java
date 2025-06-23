import java.net.*;
import java.io.*;

public class WebServer {
  public static void main(String[] args) throws Exception {
    HttpServer server = HttpServer.create(new InetSocketAddress(80), 0);
    server.createContext("/", (HttpExchange t) -> {
      String response = "Hello, Java!";
      t.sendResponseHeaders(200, response.length());
      OutputStream os = t.getResponseBody();
      os.write(response.getBytes());
      os.close();
    });
    server.setExecutor(null);
    server.start();
  }
}