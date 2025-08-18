import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpServerExample {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);

        server.createContext("/login", new LoginHandler());
        server.createContext("/do_login", new DoLoginHandler());
        server.createContext("/", new IndexHandler());
        server.createContext("/user_page", new UserPageHandler());
        server.createContext("/admin_page", new AdminPageHandler());

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class LoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Login Page";
            sendResponse(exchange, 200, response);
        }
    }

    static class DoLoginHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> params = parseRequestBody(exchange.getRequestBody());
                // Handle login logic here using params
                String response = "Login Successful or Failed";
                sendResponse(exchange, 200, response);
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private Map<String, String> parseRequestBody(InputStream requestBody) throws IOException {
            BufferedReader reader = new BufferedReader(new InputStreamReader(requestBody));
            StringBuilder body = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                body.append(line);
            }
            return parseParams(body.toString());
        }

        private Map<String, String> parseParams(String query) {
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

    static class IndexHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Welcome to the Index Page";
            sendResponse(exchange, 200, response);
        }
    }

    static class UserPageHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "User Page Content";
            sendResponse(exchange, 200, response);
        }
    }

    static class AdminPageHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Admin Page Content";
            sendResponse(exchange, 200, response);
        }
    }

    private static void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}