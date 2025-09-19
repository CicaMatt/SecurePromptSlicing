import java.io.*;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = generateUserInfoPage("JohnDoe", "johndoe@example.com", "123-45-6789");

            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private String generateUserInfoPage(String username, String email, String ssn) {
            return "<html><head><title>User Info</title></head>"
                    + "<body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Social Security Number: " + ssn + "</p>"
                    + "</body></html>";
        }
    }
}
