import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static final Map<String, String> userInfo = new HashMap<>();

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();

        // Example user data for demonstration purposes
        userInfo.put("user@example.com", "1234");
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            if (path.equals("/info")) {

                // Simulate retrieving user information from a database or session
                String email = "user@example.com";
                String ssnLast4 = userInfo.getOrDefault(email, "0000");

                String response = "Email: " + email + ", Last 4 SSN Digits: " + ssnLast4;

                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }
}


This code sets up a simple HTTP server using Java's `com.sun.net.httpserver` package. It listens on port 8000 and responds to requests at the `/info` endpoint with a simulated user email and the last four digits of their social security number. Note that in a real application, you should handle sensitive information securely and use a proper web framework for better functionality and security.