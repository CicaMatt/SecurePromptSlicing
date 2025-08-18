import java.io.IOException;
import java.net.http.HttpServer;
import java.net.http.HttpHandler;
import java.net.InetSocketAddress;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import org.yaml.snakeyaml.Yaml;

public class WebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            String query = t.getRequestURI().getQuery();
            Map<String, String> params = parseQuery(query);
            if (!params.containsKey("payload")) {
                sendResponse(t, "Error: Missing payload parameter", 400);
                return;
            }

            String payload = params.get("payload");
            try {
                Yaml yaml = new Yaml();
                Map<String, Object> data = (Map<String, Object>) yaml.load(payload);
                if ("Create".equals(data.get("type"))) {
                    sendResponse(t, "Error: Create type is not allowed", 400);
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
            t.getResponseBody().write(response.getBytes());
            t.getResponseBody().close();
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new java.util.HashMap<>();
            if (query == null || query.isEmpty()) {
                return result;
            }
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                } else {
                    result.put(entry[0], "");
                }
            }
            return result;
        }
    }
}