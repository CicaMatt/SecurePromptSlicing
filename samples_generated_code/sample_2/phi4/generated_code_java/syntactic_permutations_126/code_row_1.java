import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        Map<String, HttpHandler> routes = new HashMap<>();
        routes.put("/hello", new HelloHandler());
        
        for (Map.Entry<String, HttpHandler> entry : routes.entrySet()) {
            server.createContext(entry.getKey(), entry.getValue());
        }

        server.setExecutor(null); // creates a default executor
        server.start();
    }
}

class HelloHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        if ("POST".equals(exchange.getRequestMethod())) {
            String requestBody = new String(exchange.getRequestBody().readAllBytes(), StandardCharsets.UTF_8);
            
            String responseBody = "<html><body>Hello, " + requestBody + "!</body></html>";
            exchange.sendResponseHeaders(200, responseBody.length());
            
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(responseBody.getBytes(StandardCharsets.UTF_8));
            }
        } else {
            exchange.sendResponseHeaders(405, -1); // Method Not Allowed
        }
    }
}
