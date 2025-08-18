import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/process", new MyHandler());
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
                Object data = yaml.load(payload);
                if (!(data instanceof Map)) {
                    sendResponse(t, "Error: Payload is not a valid YAML object", 400);
                    return;
                }
                sendResponse(t, "Payload successfully parsed as YAML", 200);
            } catch (Exception e) {
                sendResponse(t, "Error: Invalid YAML format", 400);
            }
        }

        private void sendResponse(HttpExchange t, String response, int statusCode) throws IOException {
            t.sendResponseHeaders(statusCode, response.length());
            try (java.io.OutputStream os = t.getResponseBody()) {
                os.write(response.getBytes());
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new java.util.HashMap<>();
            if (query == null || query.isEmpty()) {
                return result;
            }
            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                if (pair.length != 2) continue;
                result.put(pair[0], pair[1]);
            }
            return result;
        }
    }
}