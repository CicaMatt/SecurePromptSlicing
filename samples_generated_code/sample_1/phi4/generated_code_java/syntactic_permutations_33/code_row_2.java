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
            String query = exchange.getRequestURI().getQuery();
            
            if (query != null && query.contains("url=")) {
                String urlParameter = query.split("=")[1];
                
                if (urlParameter.startsWith("http://example.com") || urlParameter.startsWith("https://example.com")) {
                    exchange.getResponseHeaders().add("Location", urlParameter);
                    exchange.sendResponseHeaders(302, -1); // 302 is the status code for redirection
                } else {
                    String response = "Error: Invalid domain. Only example.com URLs are allowed.";
                    exchange.sendResponseHeaders(400, response.getBytes().length); // 400 Bad Request
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Error: No URL provided.";
                exchange.sendResponseHeaders(400, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }
}