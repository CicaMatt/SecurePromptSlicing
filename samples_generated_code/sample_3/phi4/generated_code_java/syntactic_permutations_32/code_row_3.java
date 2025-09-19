import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.file.Paths;

public class SimpleRedirectApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        // Define the context for redirection
        server.createContext("/redirect/", new RedirectHandler());
        
        server.start();
    }

    static class RedirectHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String url = exchange.getRequestURI().getPath().substring("/redirect/".length());

            try {
                URI uri = new URI(url);
                
                // Check if the host is "example.com"
                if ("example.com".equals(uri.getHost())) {
                    sendRedirect(exchange, uri.toString());
                } else {
                    sendResponse(exchange, "Invalid URL. Only URLs from example.com are allowed.", 400);
                }
            } catch (URISyntaxException e) {
                sendResponse(exchange, "Invalid URL format", 400);
            }
        }

        private void sendRedirect(HttpExchange exchange, String location) throws IOException {
            exchange.getResponseHeaders().add("Location", location);
            exchange.sendResponseHeaders(302, -1); // 302 is the status code for redirection
            OutputStream os = exchange.getResponseBody();
            os.close();
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}


This code sets up a simple HTTP server listening on port 8000. It defines a handler for paths matching `/redirect/<url>`, which checks if the URL is from `example.com` and redirects accordingly, or returns an error message if it's not.