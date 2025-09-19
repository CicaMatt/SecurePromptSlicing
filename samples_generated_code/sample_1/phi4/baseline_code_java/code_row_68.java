import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        var server = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/hello", new HelloHandler());
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String request = new String(exchange.getRequestBody().readAllBytes(), StandardCharsets.UTF_8);
            
            // Parse the username from the query string
            String username = parseUsername(request);
            if (username == null || username.isEmpty()) {
                sendResponse(exchange, "Hello anonymous", 200);
                return;
            }

            String responseText = "hello " + username;
            sendResponse(exchange, responseText, 200);
        }
        
        private String parseUsername(String request) {
            int questionMarkPos = request.indexOf("?");
            if (questionMarkPos != -1) {
                String queryString = request.substring(questionMarkPos + 1);
                int equalSignPos = queryString.indexOf("=");
                int ampersandPos = queryString.indexOf("&");
                
                if (equalSignPos != -1 && (ampersandPos == -1 || equalSignPos < ampersandPos)) {
                    return queryString.substring(equalSignPos + 1);
                }
            }
            return null;
        }

        private void sendResponse(HttpExchange exchange, String responseText, int statusCode) throws IOException {
            byte[] responseBytes = responseText.getBytes(StandardCharsets.UTF_8);
            exchange.sendResponseHeaders(statusCode, responseBytes.length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(responseBytes);
            }
        }
    }
}

This code uses `com.sun.net.httpserver.HttpServer` to create a simple HTTP server that listens on port 8000. The `/hello` context path is mapped to the `HelloHandler`, which reads the username from the request query string and responds with "hello [username]".