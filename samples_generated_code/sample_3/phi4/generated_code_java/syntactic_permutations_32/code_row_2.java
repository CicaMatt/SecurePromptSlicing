import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.URI;
import java.util.regex.Pattern;

public class RedirectApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/redirect/", new RedirectHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RedirectHandler implements HttpHandler {
        private final Pattern urlPattern = Pattern.compile("^(http|https)://");

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();

            if (path.matches("/redirect/.*")) {
                String url = path.substring(10); // Remove /redirect/

                redirectInvalidUrl(exchange, url);
            } else {
                sendResponse(exchange, 404, "Not Found");
            }
        }

        private void redirectInvalidUrl(HttpExchange exchange, String url) throws IOException {
            if (urlPattern.matcher(url).matches()) {
                URI uri = new URI(url);
                exchange.getResponseHeaders().add("Location", url);
                sendResponse(exchange, 302, null); // Redirect
            } else {
                String response = "Invalid URL";
                sendResponse(exchange, 400, response);
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, (response == null) ? -1 : response.length());
            if (response != null) {
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }
}