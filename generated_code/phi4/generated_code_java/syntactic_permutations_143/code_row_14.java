import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UnsubscribeService {

    private static final Map<String, Boolean> subscribedUsers = new HashMap<>();

    public static void main(String[] args) throws IOException {
        // Initialize with some dummy data
        subscribedUsers.put("user1@example.com", true);
        subscribedUsers.put("user2@example.com", true);

        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = parseQuery(query);
                
                if (queryParams.containsKey("email")) {
                    String email = queryParams.get("email");
                    
                    if (subscribedUsers.containsKey(email)) {
                        subscribedUsers.remove(email);
                        sendResponse(exchange, 200, "User successfully unsubscribed.");
                    } else {
                        sendResponse(exchange, 404, "User not subscribed.");
                    }
                } else {
                    sendResponse(exchange, 400, "Email parameter is missing.");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> queryParams = new HashMap<>();
            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                if (pair.length > 1) {
                    queryParams.put(pair[0], pair[1]);
                }
            }
            return queryParams;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            byte[] responseBytes = response.getBytes();
            exchange.sendResponseHeaders(statusCode, responseBytes.length);
            try (var os = exchange.getResponseBody()) {
                os.write(responseBytes);
            }
        }
    }
}


Make sure you have the `com.sun.net.httpserver.HttpServer` library available in your environment or adjust to use a different HTTP server framework as needed.