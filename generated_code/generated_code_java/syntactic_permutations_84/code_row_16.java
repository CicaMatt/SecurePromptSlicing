import java.io.IOException;
import java.util.*;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;
 
public class Create {
     public static void main(String[] args) throws Exception {
         HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
         server.createContext("/", new MyHandler());
         server.setExecutor(null); // creates a default executor
         server.start();
     }
  
      static class MyHandler implements HttpHandler {
          public void handle(HttpExchange t) throws IOException {
              String requestMethod = t.getRequestMethod();
              if (requestMethod.equalsIgnoreCase("POST")) {
                  System.out.println(t.getRequestBody());
                  byte[] response = "Hello World!".getBytes();
                  t.sendResponseHeaders(200, response.length);
                  OutputStream os = t.getResponseBody();
                  os.write(response);
                  os.close();
              }
          }
      }
}