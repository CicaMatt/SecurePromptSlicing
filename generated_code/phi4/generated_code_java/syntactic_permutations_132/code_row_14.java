import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

public class HttpDecorator {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        // Create a map for URL paths to handler functions
        Map<String, HttpHandler> urlHandlers = new HashMap<>();
        
        urlHandlers.put("/<username>", username -> handleRequest(username, new StringReader("")));
        
        server.createContext("/", (exchange) -> {
            if (exchange.getRequestURI().getPath().matches("^/\\w+$")) {
                String username = exchange.getRequestURI().getPath().substring(1);
                HttpHandler handler = urlHandlers.get("/<username>");
                if (handler != null) {
                    handler.handle(exchange);
                } else {
                    sendResponse(exchange, 404, "Not Found");
                }
            } else {
                sendResponse(exchange, 404, "Not Found");
            }
        });

        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    private static void handleRequest(String username, Reader template) throws IOException {
        String templateContent = new String(Files.readAllBytes(Paths.get("template.html")));
        
        // Replace placeholder with actual username in the template
        String output = templateContent.replace("<%= username %>", username);

        HttpExchange exchange = null;
        try (OutputStream os = exchange.getResponseBody()) {
            sendResponse(exchange, 200, "OK", output);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void sendResponse(HttpExchange exchange, int statusCode, String statusMessage, String response) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.getBytes().length);
        try (OutputStream os = exchange.getResponseBody()) {
            byte[] responseBytes = response.getBytes();
            os.write(responseBytes);
        }
    }

    private static void sendResponse(HttpExchange exchange, int statusCode, String statusMessage) throws IOException {
        sendResponse(exchange, statusCode, statusMessage, "Not Found");
    }
}
