import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class LoginServlet {
    
    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/login", new LoginHandler());
        server.createContext("/do_login", new DoLoginHandler());

        server.start();
    }

    static class LoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>"
                    + "<form action='/do_login' method='POST'>"
                    + "Username: <input type='text' name='username'><br>"
                    + "Password: <input type='password' name='password'><br>"
                    + "<input type='submit' value='Login'>"
                    + "</form></body></html>";
            exchange.sendResponseHeaders(200, response.length());
            exchange.getResponseBody().write(response.getBytes());
            exchange.close();
        }
    }

    static class DoLoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> params = getQueryParams(exchange.getRequestBody());

                String username = params.get("username");
                String password = params.get("password");

                // For demonstration purposes only: hardcoded credentials
                if ("admin".equalsIgnoreCase(username) && "adminpass".equals(password)) {
                    redirectTo(exchange, "/admin_page");
                } else {
                    sendResponse(exchange, 200, "Login failed.");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private void redirectTo(HttpExchange exchange, String url) throws IOException {
            String response = "<html><body>Redirecting...</body></html>";
            sendResponse(exchange, 303, response);
            exchange.getResponseHeaders().add("Location", url);
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            exchange.getResponseBody().write(response.getBytes());
            exchange.close();
        }
        
        private Map<String, String> getQueryParams(InputStream requestBody) throws IOException {
            Map<String, String> params = new HashMap<>();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(requestBody))) {
                for (String line; (line = reader.readLine()) != null;) {
                    String[] keyValue = line.split("=");
                    if (keyValue.length == 2) {
                        params.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return params;
        }
    }
}