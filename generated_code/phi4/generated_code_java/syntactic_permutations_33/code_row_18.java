import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.regex.Pattern;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/redirect", new RedirectHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class RedirectHandler implements HttpHandler {
        private static final String DOMAIN = "example.com";
        private static final Pattern URL_PATTERN = Pattern.compile(
            "^https?://(www\\.)?" + DOMAIN + "(.*)$"
        );

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String urlToCheck = "http://" + (query != null ? "?" + query : "");

                if (URL_PATTERN.matcher(urlToCheck).matches()) {
                    // Redirect to the URL
                    exchange.getResponseHeaders().set("Location", urlToCheck);
                    sendResponse(exchange, 302, "Redirecting...");
                } else {
                    // Return error message
                    String response = "Error: The URL must be from domain example.com";
                    sendResponse(exchange, 400, response);
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes(StandardCharsets.UTF_8));
            }
        }
    }
}