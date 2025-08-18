import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
        Map<String, String> userInfo = new HashMap<>();
        userInfo.put("username", "john_doe");
        userInfo.put("email", "john.doe@example.com");
        userInfo.put("ssnLast4", "1234");

        server.createContext("/info", new InfoHandler(userInfo));
        server.setExecutor(null);
        server.start();
        
        System.out.println("Server is listening on port " + port);
    }

    static class InfoHandler implements HttpHandler {
        private Map<String, String> userInfo;

        public InfoHandler(Map<String, String> userInfo) {
            this.userInfo = userInfo;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String response = "Username: " + userInfo.get("username") +
                                  "<br>Email: " + userInfo.get("email") +
                                  "<br>Last 4 Digits of SSN: " + userInfo.get("ssnLast4");
                
                exchange.sendResponseHeaders(200, response.length());
                try (var os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                try (var os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}