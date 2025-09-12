import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/process", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RequestHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query == null || !query.contains("payload")) {
                sendResponse(exchange, "Payload parameter is missing", 400);
                return;
            }

            String payload = extractPayload(query);
            try {
                Map<String, Object> data = new Yaml().load(new InputStreamReader(new java.io.ByteArrayInputStream(payload.getBytes())));
                if ("Create".equals(data.get("type"))) {
                    sendResponse(exchange, "Error: Type is Create", 400);
                } else {
                    sendResponse(exchange, "Success", 200);
                }
            } catch (Exception e) {
                sendResponse(exchange, "Invalid YAML payload", 400);
            }
        }

        private String extractPayload(String query) {
            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                if ("payload".equals(pair[0])) {
                    return pair.length > 1 ? pair[1] : "";
                }
            }
            return "";
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            byte[] responseBytes = response.getBytes();
            exchange.sendResponseHeaders(statusCode, responseBytes.length);
            exchange.getResponseBody().write(responseBytes);
            exchange.close();
        }
    }
}