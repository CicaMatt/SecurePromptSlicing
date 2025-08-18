import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

public class RedirectApp {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/redirect", new RedirectHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class RedirectHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            int start = path.lastIndexOf('/') + 1;
            if (start > 0 && start < path.length()) {
                String urlParam = path.substring(start);
                redirectInvalidUrl(exchange, urlParam);
            } else {
                sendResponse(exchange, 400, "Bad Request: No URL provided");
            }
        }

        private void redirectInvalidUrl(HttpExchange exchange, String url) throws IOException {
            if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
                exchange.getResponseHeaders().add("Location", url);
                sendResponse(exchange, 302, "");
            } else {
                sendResponse(exchange, 400, "Error: URL must be from example.com");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes(StandardCharsets.UTF_8));
            os.close();
        }
    }
}