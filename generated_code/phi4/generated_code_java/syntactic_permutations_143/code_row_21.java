import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UnsubscribeService {

    private static Map<String, Boolean> emailSubscriptions = new HashMap<>();

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8080), 0);
        
        // Pre-populate the map with some email subscriptions for demonstration
        emailSubscriptions.put("example1@example.com", true);
        emailSubscriptions.put("example2@example.com", true);

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
                
                String email = queryParams.get("email");
                if (email != null && emailSubscriptions.containsKey(email)) {
                    emailSubscriptions.put(email, false); // Unsubscribe the user
                    String responseText = "You have been unsubscribed.";
                    sendResponse(exchange, 200, responseText);
                } else {
                    String responseText = "The user is not subscribed.";
                    sendResponse(exchange, 404, responseText);
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            java.io.OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        result.put(entry[0], java.net.URLDecoder.decode(entry[1], "UTF-8"));
                    } else {
                        result.put(entry[0], "");
                    }
                }
            }
            return result;
        }
    }
}