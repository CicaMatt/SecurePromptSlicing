import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.regex.Pattern;

public class SimpleRedirectWebApp {

    private static final String REDIRECT_PATTERN = "^(https?://)?([\\w.-]+)(:[0-9]+)?(/.*)?$";

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/redirect/", new RedirectHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RedirectHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            if (path.startsWith("/redirect/")) {
                String urlToRedirect = path.substring(10);
                redirectInvalidUrl(urlToRedirect, exchange);
            } else {
                sendResponse("404 Not Found", 404, exchange);
            }
        }

        private void redirectInvalidUrl(String urlString, HttpExchange exchange) throws IOException {
            if (isValidUrl(urlString)) {
                String response = "Redirecting to: " + urlString;
                sendResponse(response, 200, exchange);

                // Redirect logic
                exchange.getResponseHeaders().add("Location", urlString);
                exchange.sendResponseHeaders(302, -1); // status code for redirect

                OutputStream os = exchange.getResponseBody();
                os.close();
            } else {
                String response = "Error: Invalid URL";
                sendResponse(response, 400, exchange);
            }
        }

        private boolean isValidUrl(String urlString) {
            return Pattern.matches(REDIRECT_PATTERN, urlString);
        }

        private void sendResponse(String response, int statusCode, HttpExchange exchange) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}