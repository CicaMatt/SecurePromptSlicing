import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/redirect", new RedirectHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RedirectHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if (exchange.getRequestMethod().equalsIgnoreCase("GET")) {
                String url = exchange.getRequestURI().getQuery();
                
                if (url != null && url.contains("example.com")) {
                    sendResponse(exchange, "Redirecting to: " + url);
                } else {
                    sendResponse(exchange, "Invalid URL. Domain must be example.com");
                }
            }
        }

        private void sendResponse(HttpExchange exchange, String response) throws IOException {
            byte[] bytes = response.getBytes();
            exchange.sendResponseHeaders(200, bytes.length);
            OutputStream os = exchange.getResponseBody();
            os.write(bytes);
            os.close();
        }
    }
}