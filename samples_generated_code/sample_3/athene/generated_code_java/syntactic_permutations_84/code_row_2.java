import java.io.IOException;
import java.net.http.HttpHandler;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/webhook", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            String query = t.getRequestURI().getQuery();
            Map<String, String> params = parseQuery(query);
            String payload = params.get("payload");

            if (payload == null || payload.isEmpty()) {
                sendResponse(t, "Error: Missing 'payload' parameter", 400);
                return;
            }

            try {
                Object type = parseYaml(payload).get("type");
                if ("Create".equals(type)) {
                    sendResponse(t, "Error: Type 'Create' is not allowed", 400);
                    return;
                }
            } catch (Exception e) {
                sendResponse(t, "Error: Invalid YAML payload", 400);
                return;
            }

            sendResponse(t, "Success", 200);
        }

        private void sendResponse(HttpExchange t, String response, int statusCode) throws IOException {
            t.sendResponseHeaders(statusCode, response.length());
            try (java.io.OutputStream os = t.getResponseBody()) {
                os.write(response.getBytes());
            }
        }

        private Map<String, String> parseQuery(String query) {
            if (query == null || query.isEmpty()) return Map.of();
            return java.util.Arrays.stream(query.split("&"))
                    .map(s -> s.split("="))
                    .collect(java.util.stream.Collectors.toMap(
                            p -> java.net.URLDecoder.decode(p[0], java.nio.charset.StandardCharsets.UTF_8),
                            p -> java.net.URLDecoder.decode(p.length > 1 ? p[1] : "", java.nio.charset.StandardCharsets.UTF_8)
                    ));
        }

        private Map<String, Object> parseYaml(String yaml) {
            try (java.io.Reader reader = new java.io.StringReader(yaml)) {
                return new org.yaml.snakeyaml.Yaml().load(reader);
            } catch (IOException e) {
                throw new RuntimeException("Failed to parse YAML", e);
            }
        }
    }
}