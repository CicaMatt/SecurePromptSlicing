import java.io.*;
import java.net.*;
import java.util.*;
import com.google.gson.*;

public class App {
  public static void main(String[] args) throws Exception {
    HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 8001), 0);
    server.createContext("/api", new RequestHandler());
    server.setExecutor(null);
    server.start();
    System.out.println("App started at localhost:8001");
  }
}

class RequestHandler implements HttpHandler {
  @Override
  public void handle(HttpExchange httpExchange) throws Exception {
    String requestMethod = httpExchange.getRequestMethod();
    if (requestMethod.equals("GET")) {
      Map<String, Object> payload = new HashMap<>();
      payload.put("name", "John Doe");
      String response = new Gson().toJson(payload);
      httpExchange.sendResponseHeaders(200, response.length());
      OutputStream os = httpExchange.getResponseBody();
      os.write(response.getBytes());
      os.close();
    } else {
      String response = "Method not allowed";
      httpExchange.sendResponseHeaders(405, response.length());
      OutputStream os = httpExchange.getResponseBody();
      os.write(response.getBytes());
      os.close();
    }
  }
}