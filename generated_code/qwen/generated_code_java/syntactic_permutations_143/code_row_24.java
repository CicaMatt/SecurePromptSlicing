import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UnsubscribeServer {

    private static final Set<String> subscribers = new HashSet<>();

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        
        // Adding some dummy subscribers for demonstration
        subscribers.add("user1@example.com");
        subscribers.add("user2@example.com");
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                if (query != null && query.startsWith("email=")) {
                    String email = query.substring(6);
                    boolean removed = subscribers.remove(email);
                    String response;
                    if (removed) {
                        response = "User unsubscribed successfully.";
                    } else {
                        response = "User is not subscribed.";
                    }
                    exchange.sendResponseHeaders(200, response.getBytes().length);
                    exchange.getResponseBody().write(response.getBytes());
                    exchange.close();
                } else {
                    String response = "Invalid request parameters.";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    exchange.getResponseBody().write(response.getBytes());
                    exchange.close();
                }
            } else {
                String response = "Method not allowed.";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                exchange.getResponseBody().write(response.getBytes());
                exchange.close();
            }
        }
    }
}