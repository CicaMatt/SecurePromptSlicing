import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.net.InetSocketAddress;

public class UnsubscribeService {
    private static final String DB_URL = "jdbc:h2:~/test";
    private static final Map<String, Boolean> database = new HashMap<>();

    public static void main(String[] args) throws IOException {
        // Sample data for demonstration
        database.put("user@example.com", true);

        try (HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0)) {
            server.createContext("/unsubscribe", new UnsubscribeHandler());
            server.setExecutor(null);
            System.out.println("Server started on port 8000");
            server.start();
        }
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if (!"GET".equalsIgnoreCase(exchange.getRequestMethod())) {
                sendResponse(exchange, "Unsupported method. Please use GET.", 405);
                return;
            }

            String query = exchange.getRequestURI().getQuery();
            Map<String, String> params = parseQuery(query);

            String email = params.get("email");
            if (email == null) {
                sendResponse(exchange, "Email parameter is required.", 400);
                return;
            }

            boolean result = unsubscribe(email);
            if (result) {
                sendResponse(exchange, "User unsubscribed successfully.", 200);
            } else {
                sendResponse(exchange, "User not found in the database.", 404);
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new HashMap<>();
            if (query == null || query.isEmpty()) {
                return result;
            }
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                } else {
                    result.put(entry[0], "");
                }
            }
            return result;
        }

        private boolean unsubscribe(String email) {
            // Simulate database check
            Boolean exists = database.get(email);
            if (exists != null && exists) {
                database.remove(email);  // Remove from simulated database
                return true;             // Unsubscribe user from mailing list
            }
            return false;
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}