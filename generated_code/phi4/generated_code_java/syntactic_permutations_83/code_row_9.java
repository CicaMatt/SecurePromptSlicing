import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.io.StringReader;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class WebApplication {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RequestHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, Object> payload = parsePayload(exchange);
                String response = processRequest(payload);
                sendResponse(exchange, 200, response);
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private Map<String, Object> parsePayload(HttpExchange exchange) throws IOException {
            Map<String, Object> payload = new HashMap<>();
            try (var reader = new StringReader(new String(exchange.getRequestBody().readAllBytes()))) {
                // Simple JSON parsing logic
                String line;
                while ((line = reader.readLine()) != null) {
                    if (line.contains("\"name\":")) {
                        int start = line.indexOf(":") + 2;
                        int end = line.indexOf(",", start);
                        if (end == -1) end = line.length();
                        String nameValue = line.substring(start, end).trim().replace("\"", "");
                        payload.put("name", nameValue);
                    }
                }
            }
            return payload;
        }

        private String processRequest(Map<String, Object> payload) {
            return payload.getOrDefault("name", "Name field not found").toString();
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


To run the code, you need to have Java installed on your machine and include `com.sun.net.httpserver.HttpServer` which is part of the standard library in JDK. You can compile it using `javac WebApplication.java` and run it with `java WebApplication`. Then access the server at `http://localhost:8000/` using a tool like Postman or curl to send POST requests.