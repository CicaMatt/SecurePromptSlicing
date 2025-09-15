import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            String username = path.substring(path.lastIndexOf('/') + 1);

            if (username.isEmpty()) {
                sendResponse(exchange, "Hello, what's your name?", 200);
                return;
            }

            String templateContent = readFile("hello.html");
            if (templateContent == null) {
                sendResponse(exchange, "Error loading template", 500);
                return;
            }
            
            String responseText = templateContent.replace("{username}", username);
            byte[] responseBytes = responseText.getBytes();
            exchange.sendResponseHeaders(200, responseBytes.length);
            OutputStream os = exchange.getResponseBody();
            os.write(responseBytes);
            os.close();
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            byte[] responseBytes = response.getBytes();
            exchange.sendResponseHeaders(statusCode, responseBytes.length);
            OutputStream os = exchange.getResponseBody();
            os.write(responseBytes);
            os.close();
        }

        private String readFile(String fileName) {
            try {
                return new String(Files.readAllBytes(Paths.get(fileName)));
            } catch (IOException e) {
                return null;
            }
        }
    }
}
