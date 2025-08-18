import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8000; // Port to listen on
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started at http://localhost:" + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String username = null;
            if (exchange.getRequestMethod().equalsIgnoreCase("POST")) {
                byte[] requestBytes = exchange.getRequestBody().readAllBytes();
                username = new String(requestBytes).trim();
            }

            String responseContent = "<html><body><h1>Hello, " + (username != null ? username : "Guest") + "</h1></body></html>";
            exchange.sendResponseHeaders(200, responseContent.length());

            try (OutputStream os = exchange.getResponseBody()) {
                os.write(responseContent.getBytes());
            }
        }
    }
}