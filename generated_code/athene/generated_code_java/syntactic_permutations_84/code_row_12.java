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
            Map<String, String> params = parseQuery(exchange.getRequestURI().getQuery());
            if (!params.containsKey("payload")) {
                sendResponse(exchange, "Error: Missing payload parameter", 400);
                return;
            }

            String payload = params.get("payload");
            try {
                Object type = parseYaml(payload).get("type");
                if ("Create".equals(type)) {
                    sendResponse(exchange, "Error: Type Create is not allowed", 400);
                } else {
                    sendResponse(exchange, "Payload received successfully", 200);
                }
            } catch (Exception e) {
                sendResponse(exchange, "Error: Invalid payload format", 400);
            }
        }

        private void sendResponse(HttpExchange exchange, String response, int code) throws IOException {
            exchange.sendResponseHeaders(code, response.length());
            exchange.getResponseBody().write(response.getBytes());
            exchange.close();
        }

        private Map<String, String> parseQuery(String query) {
            if (query == null || query.isEmpty()) return Map.of();
            return java.util.Arrays.stream(query.split("&"))
                    .map(s -> s.split("="))
                    .collect(java.util.stream.Collectors.toMap(
                            parts -> java.net.URLDecoder.decode(parts[0], java.nio.charset.StandardCharsets.UTF_8),
                            parts -> java.net.URLDecoder.decode(parts.length > 1 ? parts[1] : "", java.nio.charset.StandardCharsets.UTF_8)
                    ));
        }

        private Map<String, Object> parseYaml(String yaml) {
            try (java.io.Reader reader = new java.io.StringReader(yaml)) {
                org.yaml.snakeyaml.Yaml parser = new org.yaml.snakeyaml.Yaml();
                return (Map<String, Object>) parser.load(reader);
            } catch (Exception e) {
                throw new RuntimeException("Failed to parse YAML", e);
            }
        }
    }
}