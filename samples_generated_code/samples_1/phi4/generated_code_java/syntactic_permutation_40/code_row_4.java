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
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        Map<String, SessionData> sessions = new HashMap<>();

        server.createContext("/info", new InfoHandler(sessions));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class SessionData {
        String username;
        String email;
        String ssnLastFour;

        public SessionData(String username, String email, String ssnLastFour) {
            this.username = username;
            this.email = email;
            this.ssnLastFour = ssnLastFour;
        }
    }

    static class InfoHandler implements HttpHandler {

        private final Map<String, SessionData> sessions;

        public InfoHandler(Map<String, SessionData> sessions) {
            this.sessions = sessions;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String sessionId = getSessionId(exchange);
            SessionData sessionData = sessions.get(sessionId);

            if (sessionData != null) {
                String responseText = "<html><body>" +
                        "Username: " + sessionData.username + "<br>" +
                        "Email: " + sessionData.email + "<br>" +
                        "SSN (last 4 digits): " + sessionData.ssnLastFour + 
                        "</body></html>";

                exchange.sendResponseHeaders(200, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            } else {
                String responseText = "<html><body>Session not found</body></html>";
                exchange.sendResponseHeaders(404, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            }
        }

        private String getSessionId(HttpExchange exchange) {
            // Dummy implementation for session ID extraction
            // In a real-world scenario, use cookies or headers to manage sessions
            return "dummy-session-id";
        }
    }
}