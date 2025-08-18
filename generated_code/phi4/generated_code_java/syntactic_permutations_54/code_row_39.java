import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class LoginExample {

    private static final Map<String, String> users = new HashMap<>();
    
    static {
        // Example user data
        users.put("admin", "password123");
    }

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/login", new LoginHandler());
        server.createContext("/do_login", new DoLoginHandler());
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }
    
    static class LoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equalsIgnoreCase(exchange.getRequestMethod())) {
                String response = "<html><body>"
                        + "<form action='/do_login' method='POST'>"
                        + "Username: <input type='text' name='username'><br>"
                        + "Password: <input type='password' name='password'><br>"
                        + "<input type='submit' value='Login'>"
                        + "</form>"
                        + "</body></html>";
                exchange.sendResponseHeaders(200, response.length());
                
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }
    }

    static class DoLoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equalsIgnoreCase(exchange.getRequestMethod())) {
                String query = new String(exchange.getRequestBody().readAllBytes());
                
                Map<String, String> params = parseParams(query);
                String username = params.get("username");
                String password = params.get("password");
                
                if (users.containsKey(username) && users.get(username).equals(password)) {
                    if ("admin".equals(username)) {
                        redirectTo(exchange, "/dashboard.html", 302);
                    } else {
                        sendResponse(exchange, "Access Denied: User is not admin.", 403);
                    }
                } else {
                    sendResponse(exchange, "Invalid credentials", 401);
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }

        private Map<String, String> parseParams(String query) throws IOException {
            Map<String, String> result = new HashMap<>();
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], java.net.URLDecoder.decode(entry[1], "UTF-8"));
                } else {
                    result.put(entry[0], "");
                }
            }
            return result;
        }

        private void redirectTo(HttpExchange exchange, String location, int statusCode) throws IOException {
            exchange.getResponseHeaders().add("Location", location);
            sendResponse(exchange, null, statusCode);
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            if (response == null) {
                response = "";
            }
            exchange.sendResponseHeaders(statusCode, response.length());
            
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}