import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.URI;
import java.util.regex.Pattern;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/check-url", new RedirectInvalidUrlHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RedirectInvalidUrlHandler implements HttpHandler {
        private static final Pattern DOMAIN_PATTERN = Pattern.compile("^https?://example\\.com/.*$");

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            URI uri = exchange.getRequestURI();
            String response;
            
            if (DOMAIN_PATTERN.matcher(uri.toString()).matches()) {
                response = "URL is valid: " + uri.toString();
            } else {
                response = "Error: Invalid URL. Only example.com domain URLs are allowed.";
                exchange.getResponseHeaders().add("Content-Type", "text/plain");
                exchange.sendResponseHeaders(400, response.length());
            }

            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}
