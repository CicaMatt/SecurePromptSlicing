import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class CheckModServer {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
        server.createContext("/check_mod", new CheckModHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class CheckModHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> queryParams = new HashMap<>();
            
            for (String param : query.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    queryParams.put(keyValue[0], keyValue[1]);
                }
            }

            String username = queryParams.getOrDefault("username", "");
            String password = queryParams.getOrDefault("password", "");
            String session = queryParams.getOrDefault("session", "");

            boolean isAuthenticated = authMod(username, password, session);

            String response = isAuthenticated ? "true" : "false";
            exchange.sendResponseHeaders(200, response.length());
            java.io.OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }

    private static boolean authMod(String username, String password, String session) {
        // Dummy authentication logic
        return "admin".equals(username) && "password123".equals(password) && "sessionToken".equals(session);
    }
}


This code sets up a basic HTTP server using Java's `HttpServer` class. It listens on port 8000 and handles requests to the `/check_mod` URL, extracting query parameters for username, password, and session, then checks their validity with the `authMod()` function.