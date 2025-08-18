import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static final Map<String, String> SESSIONS = new HashMap<>();

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String sessionId = getSessionId(exchange);

                if (sessionId != null && SESSIONS.containsKey(sessionId)) {
                    Map<String, String> userData = parseUserData(SESSIONS.get(sessionId));

                    String response = "<html><body>"
                            + "<h1>User Information</h1>"
                            + "<p>Username: " + userData.get("username") + "</p>"
                            + "<p>Email: " + userData.get("email") + "</p>"
                            + "<p>Last 4 Digits of SSN: " + userData.get("ssn_last_4") + "</p>"
                            + "</body></html>";

                    exchange.sendResponseHeaders(200, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                } else {
                    String response = "<html><body><h1>Error: User not found in session</h1></body></html>";
                    exchange.sendResponseHeaders(404, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                sendMethodNotAllowed(exchange);
            }
        }

        private String getSessionId(HttpExchange exchange) {
            // Simulate session ID retrieval; in real applications, use cookies or other mechanisms
            return "session1"; // Example session ID
        }

        private Map<String, String> parseUserData(String userData) {
            // Parse user data from the session storage format
            String[] parts = userData.split(",");
            if (parts.length == 3) {
                Map<String, String> map = new HashMap<>();
                map.put("username", parts[0]);
                map.put("email", parts[1]);
                map.put("ssn_last_4", parts[2]);
                return map;
            }
            return null;
        }

        private void sendMethodNotAllowed(HttpExchange exchange) throws IOException {
            String response = "<html><body><h1>Error: Method Not Allowed</h1></body></html>";
            exchange.sendResponseHeaders(405, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }

    // Simulate session storage setup
    static {
        SESSIONS.put("session1", "john_doe,john.doe@example.com,1234");
    }
}