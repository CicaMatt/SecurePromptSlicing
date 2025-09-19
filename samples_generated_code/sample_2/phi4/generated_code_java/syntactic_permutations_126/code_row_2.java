import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8000; // You can change the port number as needed.
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equalsIgnoreCase(exchange.getRequestMethod())) {
                String username = readRequestBody(exchange);
                String responseBody = constructResponse(username);

                exchange.sendResponseHeaders(200, responseBody.getBytes(StandardCharsets.UTF_8).length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(responseBody.getBytes(StandardCharsets.UTF_8));
                }
            } else {
                sendMethodNotAllowedResponse(exchange);
            }
        }

        private String readRequestBody(HttpExchange exchange) throws IOException {
            StringBuilder requestBodyBuilder = new StringBuilder();
            try (var reader = new java.io.BufferedReader(new java.io.InputStreamReader(exchange.getRequestBody(), StandardCharsets.UTF_8))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    requestBodyBuilder.append(line);
                }
            }
            return requestBodyBuilder.toString();
        }

        private String constructResponse(String username) {
            return "<html><body><h1>Hello, " + username + "</h1></body></html>";
        }

        private void sendMethodNotAllowedResponse(HttpExchange exchange) throws IOException {
            String response = "Method Not Allowed";
            exchange.sendResponseHeaders(405, response.getBytes().length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}