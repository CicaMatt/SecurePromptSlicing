import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class LoginServer {

    private static final Map<String, String> users = new HashMap<>();

    static {
        // Predefined user for demonstration
        users.put("admin", "password123");
    }

    public static void main(String[] args) throws IOException {
        int serverPort = 8000;
        HttpServer httpd = HttpServer.create(new InetSocketAddress(serverPort), 0);
        httpd.createContext("/login_form", new LoginFormHandler());
        httpd.createContext("/do_login", new DoLoginHandler());
        httpd.setExecutor(null); // creates a default executor
        httpd.start();
        System.out.println("Server started on port " + serverPort);
    }

    static class LoginFormHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String response = "<html><body>"
                        + "<form action='/do_login' method='POST'>"
                        + "Username: <input type='text' name='username'><br>"
                        + "Password: <input type='password' name='password'><br>"
                        + "<input type='submit' value='Login'>"
                        + "</form></body></html>";

                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                sendNotFound(exchange);
            }
        }
    }

    static class DoLoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestBody()
                        .toString();
                Map<String, String> parameters = parseQuery(query);
                String username = parameters.get("username");
                String password = parameters.get("password");

                if (users.containsKey(username) && users.get(username).equals(password)) {
                    if ("admin".equals(username)) {
                        redirectToAdminPage(exchange);
                    } else {
                        sendResponse(exchange, "Welcome User!");
                    }
                } else {
                    sendResponse(exchange, "Invalid credentials. Please try again.");
                }
            } else {
                sendNotFound(exchange);
            }
        }
    }

    private static void sendNotFound(HttpExchange exchange) throws IOException {
        String response = "Not Found";
        exchange.sendResponseHeaders(404, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }

    private static void redirectToAdminPage(HttpExchange exchange) throws IOException {
        String response = "Redirecting to Admin Page...";
        exchange.getResponseHeaders().add("Location", "/admin_page");
        exchange.sendResponseHeaders(302, response.length()); // 302 is the status code for redirection
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }

    private static void sendResponse(HttpExchange exchange, String response) throws IOException {
        exchange.sendResponseHeaders(200, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }

    private static Map<String, String> parseQuery(String query) {
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
}