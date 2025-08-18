import java.io.IOException;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HelloServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            String[] parts = path.split("/");
            if (parts.length > 2) {
                String username = escape(parts[2]);
                String response = hello(username);
                exchange.sendResponseHeaders(200, response.getBytes().length);
                exchange.getResponseBody().write(response.getBytes());
            } else {
                exchange.sendResponseHeaders(400, "Invalid request".getBytes().length);
                exchange.getResponseBody().write("Invalid request".getBytes());
            }
        }

        private String hello(String username) {
            return "Hello " + username;
        }

        private String escape(String input) {
            return URLEncoder.encode(input, StandardCharsets.UTF_8.toString());
        }
    }
}