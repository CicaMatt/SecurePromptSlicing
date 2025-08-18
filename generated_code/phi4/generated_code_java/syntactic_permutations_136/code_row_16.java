import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class CheckMod {

    private static final Map<String, String> users = new HashMap<>();

    static {
        // Example user credentials
        users.put("user1", "password1");
        users.put("user2", "password2");
    }

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
            if ("POST".equals(exchange.getRequestMethod())) {
                String query = new String(exchange.getRequestBody().readAllBytes());
                Map<String, String> params = parseQuery(query);

                String username = params.get("username");
                String password = params.get("password");

                String response;
                if (authenticate(username, password)) {
                    response = "true";
                } else {
                    response = "false";
                }

                exchange.sendResponseHeaders(200, response.length());
                exchange.getResponseBody().write(response.getBytes());
            }
            exchange.close();
        }

        private boolean authenticate(String username, String password) {
            return users.containsKey(username) && users.get(username).equals(password);
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new HashMap<>();
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                }
            }
            return result;
        }
    }
}