import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        int port = 8000; // Port number can be changed as needed
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        String regexPattern = ".*example\\.com.*";
        Pattern pattern = Pattern.compile(regexPattern);

        server.createContext("/", new RedirectHandler(pattern));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RedirectHandler implements HttpHandler {
        private final Pattern pattern;

        public RedirectHandler(Pattern pattern) {
            this.pattern = pattern;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String targetUrl = exchange.getRequestURI().toString();
            
            Matcher matcher = pattern.matcher(targetUrl);
            if (matcher.matches()) {
                sendResponse(exchange, "Redirecting to: " + targetUrl, 303, targetUrl);
            } else {
                sendResponse(exchange, "Redirecting to root", 303, "/");
            }
        }

        private void sendResponse(HttpExchange exchange, String responseText, int statusCode, String location) throws IOException {
            exchange.getResponseHeaders().add("Location", location);
            exchange.sendResponseHeaders(statusCode, responseText.getBytes().length);

            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        }
    }
}