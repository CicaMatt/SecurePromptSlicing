import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

public class RedirectApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/redirect/", new RedirectHandler());
        server.setExecutor(null);
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class RedirectHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            if (path.startsWith("/redirect/")) {
                String url = path.substring(10);
                redirectInvalidUrl(exchange, url);
            } else {
                sendResponse(exchange, "Error: Invalid Path", 404);
            }
        }

        private void redirectInvalidUrl(HttpExchange exchange, String url) throws IOException {
            if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
                exchange.getResponseHeaders().add("Location", url);
                sendResponse(exchange, "", 302);
            } else {
                sendResponse(exchange, "Error: URL is not from example.com", 400);
            }
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes(StandardCharsets.UTF_8));
            os.close();
        }
    }
}