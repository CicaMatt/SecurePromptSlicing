import java.io.IOException;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
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

            String payload = extractPayload(query);
            try {
                Map<String, Object> yamlMap = parseYaml(payload);
                if ("Create".equals(yamlMap.get("type"))) {
                    sendResponse(exchange, "Error: Create type not allowed", 400);
                    return;
                }
            } catch (Exception e) {
                sendResponse(exchange, "Error: Invalid YAML payload", 400);
                return;
            }

            sendResponse(exchange, "Success", 200);
        }

        private String extractPayload(String query) {
            String[] params = query.split("&");
            for (String param : params) {
                String[] pair = param.split("=");
                if ("payload".equals(pair[0])) {
                    return pair.length > 1 ? pair[1] : "";
                }
            }
            return "";
        }

        private Map<String, Object> parseYaml(String yaml) throws IOException {
            // Simple YAML parser using SnakeYAML
            org.yaml.snakeyaml.Yaml parser = new org.yaml.snakeyaml.Yaml();
            return (Map<String, Object>) parser.load(yaml);
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            byte[] respBytes = response.getBytes("UTF-8");
            exchange.sendResponseHeaders(statusCode, respBytes.length);
            exchange.getResponseBody().write(respBytes);
            exchange.close();
        }
    }
}