import java.io.IOException;
import java.net.http.HttpServer;
import java.net.http.HttpHandler;
import java.net.InetSocketAddress;
import java.util.Map;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/webhook", new WebHookHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class WebHookHandler implements HttpHandler {
        @Override
        public void handle(java.net.http.HttpExchange t) throws IOException {
            String query = t.getRequestURI().getQuery();
            Map<String, String> params = parseQuery(query);

            if (!params.containsKey("payload")) {
                sendResponse(t, "Error: payload parameter is missing", 400);
                return;
            }

            String payload = params.get("payload");
            try {
                ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
                Map<String, Object> data = yamlMapper.readValue(payload, Map.class);

                if (data.containsKey("type") && "Create".equals(data.get("type"))) {
                    sendResponse(t, "Error: type Create is not allowed", 400);
                    return;
                }

                sendResponse(t, "OK", 200);

            } catch (IOException e) {
                sendResponse(t, "Error: Invalid YAML payload", 400);
            }
        }

        private void sendResponse(java.net.http.HttpExchange t, String response, int statusCode) throws IOException {
            t.sendResponseHeaders(statusCode, response.length());
            java.io.OutputStream os = t.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> params = new java.util.HashMap<>();
            if (query == null || query.isEmpty()) {
                return params;
            }
            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                String key = java.net.URLDecoder.decode(pair[0], java.nio.charset.StandardCharsets.UTF_8);
                String value = pair.length > 1 ? java.net.URLDecoder.decode(pair[1], java.nio.charset.StandardCharsets.UTF_8) : "";
                params.put(key, value);
            }
            return params;
        }
    }
}