import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class Main {

    public static void main(String[] args) throws IOException {
        int port = 8000; // Port number for the HTTP server
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
        Map<String, String> routes = new HashMap<>();
        routes.put("/hello/.*", "HelloHandler");

        for (String urlPattern : routes.keySet()) {
            server.createContext(urlPattern, createHandler(routes.get(urlPattern)));
        }

        server.setExecutor(null); // creates a default executor
        server.start();
        
        System.out.println("Server started on port " + port);
    }
    
    private static HttpHandler createHandler(String handlerClass) {
        switch (handlerClass) {
            case "HelloHandler":
                return new HelloHandler();
            default:
                throw new IllegalArgumentException("Unknown handler: " + handlerClass);
        }
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requestUri = exchange.getRequestURI().toString();
            String[] uriParts = requestUri.split("/");
            if (uriParts.length > 2 && uriParts[1].equals("hello")) {
                String username = uriParts[2];
                String response = "Hello, " + username + "! Welcome to the server.";
                
                exchange.sendResponseHeaders(200, response.getBytes().length);
                try (var os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            } else {
                String response = "Invalid URL";
                exchange.sendResponseHeaders(404, response.getBytes().length);
                try (var os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}