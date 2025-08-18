import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static final Map<String, String> sessionVariables = new HashMap<>();

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        // Initialize some sample data in the "session"
        sessionVariables.put("username", "john_doe");
        sessionVariables.put("email", "john.doe@example.com");
        sessionVariables.put("ssn", "123-45-6789");

        server.createContext("/info", new InfoHandler());
        
        System.out.println("Server started on port " + port);
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String username = sessionVariables.get("username");
                String email = sessionVariables.get("email");
                String ssn = sessionVariables.get("ssn");

                String response = "<html><body>"
                        + "<h1>User Information</h1>"
                        + "<p>Username: " + username + "</p>"
                        + "<p>Email: " + email + "</p>"
                        + "<p>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>"
                        + "</body></html>";

                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}