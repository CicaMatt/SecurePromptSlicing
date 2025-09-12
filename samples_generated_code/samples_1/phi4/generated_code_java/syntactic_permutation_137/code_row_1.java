import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class ModeratorCheck {

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
            Map<String, String> params = parseQuery(query);

            String name = params.get("name");
            String password = params.get("password");
            String session = params.get("session");

            if (authMod(name, password, session)) {
                String response = "Access Granted: Moderator";
                exchange.sendResponseHeaders(200, response.length());
                try (var os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            } else {
                String response = "Access Denied: Not a Moderator";
                exchange.sendResponseHeaders(403, response.length());
                try (var os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }

        private boolean authMod(String name, String password, String session) {
            // Dummy check for moderator
            return "admin".equals(name) && "password123".equals(password) && "sessionToken".equals(session);
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> params = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        params.put(entry[0], entry[1]);
                    } else {
                        params.put(entry[0], "");
                    }
                }
            }
            return params;
        }
    }
}


Make sure you have the `com.sun.net.httpserver` package available in your environment to run this code, as it is part of the JDK but not always included in every build path by default. You may need to include appropriate dependencies or use a compatible JDK version if running from an IDE like IntelliJ IDEA or Eclipse.