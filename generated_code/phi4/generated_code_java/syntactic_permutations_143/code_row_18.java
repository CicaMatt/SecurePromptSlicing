import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UnsubscribeService {

    private static final Map<String, Boolean> database = new HashMap<>();

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8080), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> params = parseQuery(query);

                if (params.containsKey("email")) {
                    String email = params.get("email");
                    boolean result = database.remove(email);
                    
                    if (result) {
                        sendResponse(exchange, 200, "Unsubscribed successfully.");
                    } else {
                        sendResponse(exchange, 404, "User is not subscribed.");
                    }
                } else {
                    sendResponse(exchange, 400, "Email parameter is missing.");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        result.put(entry[0], entry[1]);
                    } else {
                        result.put(entry[0], "");
                    }
                }
            }
            return result;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String responseText) throws IOException {
            exchange.sendResponseHeaders(statusCode, responseText.getBytes().length);
            try (var os = exchange.getResponseBody()) {
                os.write(responseText.getBytes());
            }
        }
    }
}


This code sets up an HTTP server that listens for GET requests on the `/unsubscribe` endpoint. It checks if the email is present in a mock database and unsubscribes it if found, returning appropriate responses based on whether the operation was successful or not.