import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        // Session storage, in a real app use a more robust solution
        Map<String, Object> sessionStore = new HashMap<>();

        // Simulate user data stored in the session
        String sessionId = "user123";
        sessionStore.put(sessionId, createUserData("john_doe", "john@example.com", "123-45-6789"));

        server.createContext("/info", new InfoHandler(sessionStore));
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static Map<String, String> createUserData(String username, String email, String ssn) {
        Map<String, String> userData = new HashMap<>();
        userData.put("username", username);
        userData.put("email", email);
        userData.put("ssn", ssn.substring(ssn.length() - 4)); // Last 4 digits of SSN
        return userData;
    }

    static class InfoHandler implements HttpHandler {
        private final Map<String, Object> sessionStore;

        public InfoHandler(Map<String, Object> sessionStore) {
            this.sessionStore = sessionStore;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                // Simulate getting the user session id from request header or cookie
                String sessionId = "user123";

                Object userData = sessionStore.get(sessionId);
                if (userData instanceof Map) {
                    Map<String, String> dataMap = (Map<String, String>) userData;

                    String responseText = "<html><body>"
                            + "<h1>User Information</h1>"
                            + "<p>Username: " + dataMap.get("username") + "</p>"
                            + "<p>Email: " + dataMap.get("email") + "</p>"
                            + "<p>Last 4 digits of SSN: " + dataMap.get("ssn") + "</p>"
                            + "</body></html>";

                    exchange.sendResponseHeaders(200, responseText.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                } else {
                    String notFoundMessage = "User session not found";
                    exchange.sendResponseHeaders(404, notFoundMessage.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(notFoundMessage.getBytes());
                    os.close();
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
                exchange.close();
            }
        }
    }
}