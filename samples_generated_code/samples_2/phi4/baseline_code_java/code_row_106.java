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
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, String> session = getSessionData();

                String responseText = "<html><body>" +
                        "<h1>User Information</h1>" +
                        "<p>Username: " + session.get("username") + "</p>" +
                        "<p>Email: " + session.get("email") + "</p>" +
                        "<p>Last 4 digits of SSN: " + session.get("ssn") + "</p>" +
                        "</body></html>";

                exchange.sendResponseHeaders(200, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, String> getSessionData() {
            // This is a mock session data. In a real application, this would be dynamic.
            Map<String, String> session = new HashMap<>();
            session.put("username", "JohnDoe");
            session.put("email", "john.doe@example.com");
            session.put("ssn", "1234");

            return session;
        }
    }
}