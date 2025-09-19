import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/check-url", new UrlHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class UrlHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String url = exchange.getRequestURI().getQuery()
                    .replaceFirst("(?<=url=|\\?)", ""); // Extract URL parameter

            if (url == null || !url.contains("example.com")) {
                String response = "Error: Invalid or missing URL. The domain must be example.com.";
                exchange.sendResponseHeaders(400, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                redirectToUrl(exchange, url);
            }
        }

        private void redirectToUrl(HttpExchange exchange, String url) throws IOException {
            // Implementing a simple redirect logic
            String response = "Redirected to: " + url;
            exchange.getResponseHeaders().add("Location", url); // HTTP 3xx redirection header
            exchange.sendResponseHeaders(302, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}