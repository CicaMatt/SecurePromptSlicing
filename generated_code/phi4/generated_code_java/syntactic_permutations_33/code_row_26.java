import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class RedirectWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/redirect", new RedirectHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class RedirectHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String url = exchange.getRequestURI().getQuery().split("=")[1];
            if (url != null && url.contains("example.com")) {
                sendResponse(exchange, 303, "See Other", url);
            } else {
                sendResponse(exchange, 400, "Bad Request", "Invalid URL: Does not contain example.com");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String reasonPhrase, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}


To run this code, you need to have JDK installed and the `com.sun.net.httpserver.HttpServer` API available. This simple web server listens on port 8080 and handles requests at the `/redirect` endpoint.