import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleHttpServer {

    private static final String ADMIN_PAGE = "/admin_page";
    private static final String LOGIN_FORM = "<form action=\"/do_login\" method=\"post\">" +
            "Username: <input type=\"text\" name=\"username\"><br>" +
            "Password: <input type=\"password\" name=\"password\"><br>" +
            "<input type=\"submit\" value=\"Login\">" +
            "</form>";

    private static Map<String, String> userDatabase = new HashMap<>();

    public static void main(String[] args) throws IOException {
        // Populate with a sample admin user
        userDatabase.put("admin", "password");

        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/login", new LoginHandler());
        server.createContext("/do_login", new DoLoginHandler());

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class LoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String response = LOGIN_FORM;
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                sendBadRequest(exchange);
            }
        }
    }

    static class DoLoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Scanner scanner = new Scanner(exchange.getRequestBody(), StandardCharsets.UTF_8.name());
                String body = scanner.useDelimiter("\\A").next();
                scanner.close();

                Map<String, String> params = parseParams(body);
                String username = params.get("username");
                String password = params.get("password");

                if (username.equals("admin") && password.equals(userDatabase.get(username))) {
                    redirectToPage(exchange, 303, ADMIN_PAGE, "Redirecting to admin page...");
                } else {
                    sendBadRequest(exchange);
                }
            } else {
                sendBadRequest(exchange);
            }
        }

        private Map<String, String> parseParams(String body) {
            Map<String, String> params = new HashMap<>();
            for (String param : body.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    params.put(keyValue[0], keyValue[1]);
                }
            }
            return params;
        }

        private void redirectToPage(HttpExchange exchange, int statusCode, String location, String responseText) throws IOException {
            exchange.getResponseHeaders().add("Location", location);
            exchange.sendResponseHeaders(statusCode, responseText.length());
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        }
    }

    private static void sendBadRequest(HttpExchange exchange) throws IOException {
        String response = "Bad Request";
        exchange.sendResponseHeaders(400, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}