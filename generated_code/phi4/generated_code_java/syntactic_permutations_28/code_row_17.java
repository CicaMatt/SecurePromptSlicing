import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.regex.Pattern;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpRedirectServer {
    private static final String DEFAULT_URL = "http://default.url";
    
    public static void main(String[] args) throws IOException {
        int port = 8080; // Default HTTP port
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        Pattern pattern = Pattern.compile("your-regex-here"); // Replace with your actual regex
        
        server.createContext("/", new RedirectHandler(pattern, DEFAULT_URL));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RedirectHandler implements HttpHandler {
        private final Pattern pattern;
        private final String defaultUrl;

        public RedirectHandler(Pattern pattern, String defaultUrl) {
            this.pattern = pattern;
            this.defaultUrl = defaultUrl;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requestUri = exchange.getRequestURI().toString();

            if (pattern.matcher(requestUri).matches()) {
                sendResponse(exchange, "http://redirect-target.url"); // Replace with actual redirect URL
            } else {
                sendResponse(exchange, defaultUrl);
            }
        }

        private void sendResponse(HttpExchange exchange, String url) throws IOException {
            exchange.getResponseHeaders().set("Location", url);
            exchange.sendResponseHeaders(302, -1); // 302 is the status code for redirection
        }
    }
}
