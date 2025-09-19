import java.io.IOException;
import java.util.Map;

import org.yaml.snakeyaml.Yaml;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/check", new CheckHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class CheckHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> params = queryToMap(query);

            if (!params.containsKey("payload")) {
                sendResponse(exchange, "Error: No payload parameter provided", 400);
                return;
            }

            String payload = params.get("payload");
            try {
                Yaml yaml = new Yaml();
                Map<String, Object> data = yaml.load(payload);

                if ("Create".equals(data.get("type"))) {
                    sendResponse(exchange, "Error: Type Create is not allowed", 400);
                    return;
                }
            } catch (Exception e) {
                sendResponse(exchange, "Error: Failed to parse YAML payload", 400);
                return;
            }

            sendResponse(exchange, "Payload processed successfully", 200);
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            byte[] bytes = response.getBytes();
            exchange.sendResponseHeaders(statusCode, bytes.length);
            exchange.getResponseBody().write(bytes);
            exchange.close();
        }

        private Map<String, String> queryToMap(String query) {
            Map<String, String> result = java.util.stream.Stream.of(query.split("&"))
                    .collect(java.util.stream.Collectors.toMap(
                            s -> s.substring(0, s.indexOf("=")),
                            s -> s.substring(s.indexOf("=") + 1)
                    ));
            return result;
        }
    }
}