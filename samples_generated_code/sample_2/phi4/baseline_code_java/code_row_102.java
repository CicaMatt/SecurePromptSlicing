import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/checkName", new NameHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class NameHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String payload = new String(exchange.getRequestBody().readAllBytes(), StandardCharsets.UTF_8);
            Map<String, String> fields = parsePayload(payload);

            if (fields.containsKey("name")) {
                String response = "Name: " + fields.get("name");
                sendResponse(exchange, 200, response.getBytes());
            } else {
                sendResponse(exchange, 400, "Field 'name' not found".getBytes());
            }
        }

        private Map<String, String> parsePayload(String payload) {
            Map<String, String> fields = new HashMap<>();
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                try {
                    fields.put(pair.substring(0, idx), pair.substring(idx + 1));
                } catch (Exception e) {
                    // Handle malformed input
                }
            }
            return fields;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, byte[] response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length);
            OutputStream os = exchange.getResponseBody();
            os.write(response);
            os.close();
        }
    }
}