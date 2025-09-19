import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String response = "<html><body>"
                        + "<h1>User Information</h1>"
                        + "<p>Username: " + getUsername() + "</p>"
                        + "<p>Email: " + getEmail() + "</p>"
                        + "<p>Last 4 digits of SSN: " + getLastFourSSN() + "</p>"
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

        private static String getUsername() {
            return "user123"; // Replace with actual retrieval logic
        }

        private static String getEmail() {
            return "user@example.com"; // Replace with actual retrieval logic
        }

        private static String getLastFourSSN() {
            return "6789"; // Replace with actual retrieval logic
        }
    }
}