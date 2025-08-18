import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        Map<String, Map<String, String>> sessions = new HashMap<>();

        server.createContext("/info", new InfoHandler(sessions));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        private final Map<String, Map<String, String>> sessions;

        public InfoHandler(Map<String, Map<String, String>> sessions) {
            this.sessions = sessions;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String sessionId = getSessionId(exchange);
                
                if (sessionId != null && sessions.containsKey(sessionId)) {
                    Map<String, String> userData = sessions.get(sessionId);

                    String response = "Username: " + userData.get("username") +
                                      ", Email: " + userData.get("email") +
                                      ", SSN: " + userData.get("ssn");

                    sendResponse(exchange, 200, response);
                } else {
                    sendResponse(exchange, 404, "Session not found");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private String getSessionId(HttpExchange exchange) {
            String sessionId = exchange.getRequestHeaders().getFirst("Cookie");
            if (sessionId != null) {
                return sessionId.split("=")[1];
            }
            return generateNewSession();
        }

        private String generateNewSession() {
            String sessionId = UUID.randomUUID().toString();
            
            // Simulating user data
            Map<String, String> userData = new HashMap<>();
            userData.put("username", "JohnDoe");
            userData.put("email", "johndoe@example.com");
            userData.put("ssn", "123-45-6789");

            sessions.put(sessionId, userData);
            
            System.out.println("New session created: " + sessionId);

            return sessionId;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}