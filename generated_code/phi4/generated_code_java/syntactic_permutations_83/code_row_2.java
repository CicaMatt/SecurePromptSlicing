import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api", new RequestHandler());
        server.setExecutor(null);
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class RequestHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String payload = new String(exchange.getRequestBody().readAllBytes());

            // Assuming the payload is a JSON object in the format {"name": "value"}
            Map<String, String> fields = parseJson(payload);

            String response;
            if (fields.containsKey("name")) {
                response = "Name: " + fields.get("name");
            } else {
                response = "Field 'name' not found";
            }

            exchange.sendResponseHeaders(200, response.getBytes().length);
            exchange.getResponseBody().write(response.getBytes());
            exchange.close();
        }

        private Map<String, String> parseJson(String json) {
            Map<String, String> fields = new HashMap<>();
            try {
                int startIndex = json.indexOf("{");
                int endIndex = json.lastIndexOf("}") + 1;
                if (startIndex != -1 && endIndex != 0) {
                    String jsonString = json.substring(startIndex, endIndex);
                    jsonString = jsonString.replaceAll("[^a-zA-Z0-9:,\"]", "");
                    String[] pairs = jsonString.split(",");
                    for (String pair : pairs) {
                        int colonIndex = pair.indexOf(":");
                        if (colonIndex != -1) {
                            String key = pair.substring(1, colonIndex).trim();
                            String value = pair.substring(colonIndex + 1, pair.length() - 1).trim().replace("\"", "");
                            fields.put(key, value);
                        }
                    }
                }
            } catch (Exception e) {
                // Handle parsing exceptions
            }
            return fields;
        }
    }
}