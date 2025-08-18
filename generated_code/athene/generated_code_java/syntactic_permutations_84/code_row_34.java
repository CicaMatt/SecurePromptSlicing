import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.InetSocketAddress;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/webhook", new WebHookHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class WebHookHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query == null || !query.contains("payload")) {
                sendResponse(exchange, "Error: Missing payload parameter", 400);
                return;
            }

            Map<String, String> params = parseQuery(query);
            String payload = params.get("payload");
            try {
                Yaml yaml = new Yaml();
                Object data = yaml.load(payload);

                if (!(data instanceof Map)) {
                    sendResponse(exchange, "Error: Payload is not a valid YAML map", 400);
                    return;
                }

                // If the type check passed, you can proceed with further processing
                sendResponse(exchange, "Success: Valid payload received", 200);

            } catch (Exception e) {
                sendResponse(exchange, "Error: Invalid YAML format", 400);
            }
        }

        private void sendResponse(HttpExchange exchange, String response, int status) throws IOException {
            byte[] responseBytes = response.getBytes();
            exchange.sendResponseHeaders(status, responseBytes.length);
            exchange.getResponseBody().write(responseBytes);
            exchange.close();
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> params = new java.util.HashMap<>();
            if (query == null || query.isEmpty()) return params;

            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                if (pair.length > 1) {
                    params.put(pair[0], pair[1]);
                } else {
                    params.put(pair[0], "");
                }
            }
            return params;
        }
    }
}