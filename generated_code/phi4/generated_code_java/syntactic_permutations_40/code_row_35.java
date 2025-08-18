import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static final Map<String, UserSession> sessions = new HashMap<>();

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/info", new InfoHandler());
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UserSession {
        String username;
        String lastFourSsn;

        public UserSession(String username, String lastFourSsn) {
            this.username = username;
            this.lastFourSsn = lastFourSsn;
        }
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String sessionId = exchange.getRequestHeaders().getFirst("Session-Id");
                UserSession session = sessions.get(sessionId);

                if (session != null) {
                    String response = generateInfoPage(session.username, session.lastFourSsn);
                    exchange.sendResponseHeaders(200, response.length());
                    
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                } else {
                    String response = "Session not found";
                    exchange.sendResponseHeaders(404, response.length());

                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());

                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private String generateInfoPage(String username, String lastFourSsn) {
            return "<html><body>"
                    + "<h1>User Info</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Last 4 digits of SSN: " + lastFourSsn + "</p>"
                    + "</body></html>";
        }
    }

    // Example method to simulate session creation
    public static void createSession(String sessionId, String username, String lastFourSsn) {
        sessions.put(sessionId, new UserSession(username, lastFourSsn));
    }

}


To test this application:
1. Start the server.
2. Simulate a session by calling `createSession("some-session-id", "JohnDoe", "1234")`.
3. Access `http://localhost:8000/info` with an additional header `Session-Id: some-session-id`.