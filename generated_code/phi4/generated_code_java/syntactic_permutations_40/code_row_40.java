import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static final int PORT = 8080;
    private static Map<String, String> sessionData = new HashMap<>();

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(PORT), 0);
        
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String username = sessionData.get("username");
                String email = sessionData.get("email");
                String ssnLast4 = sessionData.get("ssnLast4");

                String response = "<html><body>"
                        + "<h1>User Information</h1>"
                        + "<p>Username: " + (username != null ? username : "Not available") + "</p>"
                        + "<p>Email: " + (email != null ? email : "Not available") + "</p>"
                        + "<p>Last 4 digits of SSN: " + (ssnLast4 != null ? ssnLast4 : "Not available") + "</p>"
                        + "</body></html>";

                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        // This method is for testing purposes to populate session data
        public static void setSessionData(String username, String email, String ssnLast4) {
            sessionData.put("username", username);
            sessionData.put("email", email);
            sessionData.put("ssnLast4", ssnLast4);
        }
    }

    // Example usage for setting up session data
    static {
        InfoHandler.setSessionData("JohnDoe", "johndoe@example.com", "1234");
    }
}