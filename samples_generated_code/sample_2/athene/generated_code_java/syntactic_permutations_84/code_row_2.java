import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/webhook", new WebhookHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class WebhookHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            Map<String, String> params = parseQuery(exchange.getRequestURI().getQuery());

            if (!params.containsKey("payload")) {
                sendResponse(exchange, "Error: Payload parameter is missing", 400);
                return;
            }

            String payload = params.get("payload");
            try {
                Yaml yaml = new Yaml();
                Map<String, Object> data = (Map<String, Object>) yaml.load(payload);

                if ("Create".equals(data.get("type"))) {
                    sendResponse(exchange, "Error: Create type is not allowed", 400);
                    return;
                }

                sendResponse(exchange, "Payload received successfully", 200);
            } catch (Exception e) {
                sendResponse(exchange, "Error: Invalid YAML payload", 400);
            }
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Map<String, String> parseQuery(String query) {
            if (query == null || query.isEmpty()) {
                return Map.of();
            }
            return Arrays.stream(query.split("&"))
                         .map(s -> s.split("="))
                         .collect(Collectors.toMap(
                             pair -> URLDecoder.decode(pair[0], StandardCharsets.UTF_8),
                             pair -> URLDecoder.decode(pair.length > 1 ? pair[1] : "", StandardCharsets.UTF_8)
                         ));
        }
    }
}