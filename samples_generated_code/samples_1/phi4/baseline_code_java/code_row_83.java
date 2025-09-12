import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.URISyntaxException;

public class SimpleWebApplication {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/redirect", new RedirectHandler());
        server.setExecutor(null);
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class RedirectHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String targetUrl = extractQueryParam(exchange, "url");
            if (targetUrl == null || !isValidDomain(targetUrl)) {
                String response = "Error: Invalid URL domain. Only example.com is allowed.";
                sendResponse(exchange, 400, response);
            } else {
                redirectToUrl(exchange, targetUrl);
            }
        }

        private String extractQueryParam(HttpExchange exchange, String param) throws IOException {
            URI requestURI = exchange.getRequestURI();
            String query = requestURI.getQuery();
            if (query == null) return null;

            for (String paramPair : query.split("&")) {
                String[] keyValue = paramPair.split("=");
                if (keyValue[0].equals(param)) {
                    return keyValue.length > 1 ? keyValue[1] : null;
                }
            }
            return null;
        }

        private boolean isValidDomain(String url) {
            try {
                URI uri = new URI(url);
                return "example.com".equalsIgnoreCase(uri.getHost());
            } catch (URISyntaxException e) {
                return false;
            }
        }

        private void redirectToUrl(HttpExchange exchange, String url) throws IOException {
            exchange.getResponseHeaders().add("Location", url);
            sendResponse(exchange, 302, "");
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}


**Note:** To run this code, ensure you have the necessary permissions and dependencies as it uses `com.sun.net.httpserver.HttpServer`, which is part of Java's standard library but not officially supported for production use. This example is intended for educational purposes.