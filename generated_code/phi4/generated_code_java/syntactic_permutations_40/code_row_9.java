import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static final int PORT = 8000;

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(PORT), 0);
        
        Map<String, UserSession> sessions = new HashMap<>();
        
        server.createContext("/info", new InfoHandler(sessions));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        private final Map<String, UserSession> sessions;

        public InfoHandler(Map<String, UserSession> sessions) {
            this.sessions = sessions;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String sessionId = getSessionId(exchange);
            if (sessionId == null || !sessions.containsKey(sessionId)) {
                sendResponse(exchange, 401, "Unauthorized");
                return;
            }
            
            UserSession userSession = sessions.get(sessionId);
            String responseText = info(userSession);
            sendResponse(exchange, 200, responseText);
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
        
        private String getSessionId(HttpExchange exchange) {
            String cookieHeader = exchange.getRequestHeaders().getFirst("Cookie");
            if (cookieHeader != null && cookieHeader.startsWith("SESSIONID=")) {
                return cookieHeader.substring(10);
            }
            return null;
        }

        private String info(UserSession userSession) {
            return "Username: " + userSession.getUsername() +
                   "<br>Email: " + userSession.getEmail() +
                   "<br>Last 4 SSN Digits: " + userSession.getSsn().substring(userSession.getSsn().length() - 4);
        }
    }

    static class UserSession {
        private final String username;
        private final String email;
        private final String ssn;

        public UserSession(String username, String email, String ssn) {
            this.username = username;
            this.email = email;
            this.ssn = ssn;
        }

        public String getUsername() {
            return username;
        }

        public String getEmail() {
            return email;
        }

        public String getSsn() {
            return ssn;
        }
    }
}