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
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        // Setting up session storage
        Map<String, UserSession> sessions = new HashMap<>();
        
        // Define handler for /info route
        server.createContext("/info", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String sessionId = exchange.getRequestHeaders().getFirst("Cookie");
                
                UserSession session = sessions.get(sessionId);
                if (session != null) {
                    StringBuilder response = new StringBuilder();
                    response.append("<html><body>");
                    response.append("<h1>User Information</h1>");
                    response.append("<p>Username: ").append(session.getUsername()).append("</p>");
                    response.append("<p>Email: ").append(session.getEmail()).append("</p>");
                    response.append("<p>Last 4 SSN Digits: ").append(session.getSsn().substring(session.getSsn().length() - 4)).append("</p>");
                    response.append("</body></html>");

                    exchange.sendResponseHeaders(200, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.toString().getBytes());
                    os.close();
                } else {
                    exchange.sendResponseHeaders(404, -1);
                    exchange.getResponseBody().close();
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
                exchange.getResponseBody().close();
            }
        }));

        server.setExecutor(null); // creates a default executor
        server.start();
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