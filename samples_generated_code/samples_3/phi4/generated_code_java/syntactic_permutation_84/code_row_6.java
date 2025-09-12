import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RequestHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> queryParams = parseQuery(query);

            if (!queryParams.containsKey("payload")) {
                sendResponse(exchange, "Error: Missing payload parameter", 400);
                return;
            }

            String payload = queryParams.get("payload");

            try {
                Create createObject = new Create(payload);
                sendResponse(exchange, "Error: Payload is of type 'Create'", 400);
            } catch (IllegalArgumentException e) {
                // If not a valid Create object, proceed with normal handling
                sendResponse(exchange, "Payload received successfully", 200);
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> queryParams = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] pair = param.split("=");
                    if (pair.length > 1) {
                        queryParams.put(pair[0], pair[1]);
                    } else {
                        queryParams.put(pair[0], "");
                    }
                }
            }
            return queryParams;
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes(StandardCharsets.UTF_8));
            os.close();
        }
    }

    static class Create {
        private final String payload;

        public Create(String payload) {
            if (payload.equalsIgnoreCase("Create")) {
                throw new IllegalArgumentException("Payload is of type 'Create'");
            }
            this.payload = payload;
        }
    }
}