import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleHttpServer {

    private static final Map<String, String> USER_CREDENTIALS = new HashMap<>();
    
    // Initialize user credentials
    static {
        USER_CREDENTIALS.put("admin", "password123");  // Example admin credentials
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
            if ("GET".equals(exchange.getRequestMethod())) {
                String response = "<html><body>" +
                        "<form action=\"/do_login\" method=\"post\">" +
                        "Username: <input type=\"text\" name=\"username\"><br>" +
                        "Password: <input type=\"password\" name=\"password\"><br>" +
                        "<input type=\"submit\" value=\"Login\">" +
                        "</form>" +
                        "</body></html>";
                
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                sendErrorResponse(exchange, 405);
            }
        }
    }

    static class DoLoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String query = new String(exchange.getRequestBody().readAllBytes());
                Map<String, String> parameters = parseQuery(query);

                String username = parameters.get("username");
                String password = parameters.get("password");

                if (USER_CREDENTIALS.containsKey(username) && USER_CREDENTIALS.get(username).equals(password)) {
                    String response = "<html><body>You are an admin. <a href=\"/admin_page\">Go to Admin Page</a></body></html>";
                    
                    exchange.getResponseHeaders().add("Location", "/admin_page");
                    exchange.sendResponseHeaders(302, response.length());
                } else {
                    sendErrorResponse(exchange, 401);
                }

                OutputStream os = exchange.getResponseBody();
                if (exchange.getStatusCode() == 302) {
                    os.write("<html><body>Redirecting...</body></html>".getBytes());
                }
                os.close();
            } else {
                sendErrorResponse(exchange, 405);
            }
        }
    }

    static Map<String, String> parseQuery(String query) {
        Map<String, String> result = new HashMap<>();
        for (String param : query.split("&")) {
            String[] entry = param.split("=");
            if (entry.length > 1) {
                result.put(entry[0], entry[1]);
            } else {
                result.put(entry[0], "");
            }
        }
        return result;
    }

    static void sendErrorResponse(HttpExchange exchange, int statusCode) throws IOException {
        String response = "Error: Invalid request method or credentials.";
        exchange.sendResponseHeaders(statusCode, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}