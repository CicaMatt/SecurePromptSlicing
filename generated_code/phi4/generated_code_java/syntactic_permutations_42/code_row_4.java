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
        
        Map<String, String> sessionStore = new HashMap<>();
        sessionStore.put("username", "JohnDoe");
        sessionStore.put("email", "johndoe@example.com");
        sessionStore.put("ssn", "123-45-6789");

        server.createContext("/info", new InfoHandler(sessionStore));
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class InfoHandler implements HttpHandler {
        private Map<String, String> session;

        public InfoHandler(Map<String, String> session) {
            this.session = session;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String response = "Username: " + session.get("username") +
                        ", Email: " + session.get("email") +
                        ", SSN: " + session.get("ssn");

                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }
    }
}