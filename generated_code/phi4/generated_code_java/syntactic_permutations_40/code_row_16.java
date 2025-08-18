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
        
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class InfoHandler implements HttpHandler {
        private static final ThreadLocal<Map<String, String>> session = ThreadLocal.withInitial(HashMap::new);

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            // Sample data to simulate session storage
            Map<String, String> userSession = session.get();
            if (userSession == null || !userSession.containsKey("username") ||
                    !userSession.containsKey("email") || 
                    !userSession.containsKey("ssn")) {

                String response = "User not found in session";
                exchange.sendResponseHeaders(404, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
                return;
            }

            String username = userSession.get("username");
            String email = userSession.get("email");
            String ssn = userSession.get("ssn");

            // Only show the last 4 digits of SSN
            String maskedSsn = "****-" + ssn.substring(ssn.length() - 4);

            String response = "<html><body>" +
                    "<h1>User Info</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Last 4 of SSN: " + maskedSsn + "</p>" +
                    "</body></html>";

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }

    public static void main(String[] args) throws IOException {
        // Example of setting session data
        Map<String, String> userSession = new HashMap<>();
        userSession.put("username", "john_doe");
        userSession.put("email", "john.doe@example.com");
        userSession.put("ssn", "123-45-6789");

        InfoHandler.session.set(userSession);

        SimpleWebApp.main(args); // Start the server
    }
}