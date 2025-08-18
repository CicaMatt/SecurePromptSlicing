import java.io.IOException;
import java.net.http.HttpHandler;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/process", SimpleWebApp::handleRequest);
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleRequest(HttpExchange exchange) throws IOException {
        String response = "";
        try {
            Map<String, String> queryPairs = new java.util.LinkedHashMap<>();
            String query = exchange.getRequestURI().getQuery();
            if (query == null || query.isEmpty()) {
                response = "Error: Missing payload parameter";
                sendResponse(400, response, exchange);
                return;
            }

            for (String pair : query.split("&")) {
                int idx = pair.indexOf("=");
                queryPairs.put(java.net.URLDecoder.decode(pair.substring(0, idx), "UTF-8"), java.net.URLDecoder.decode(pair.substring(idx + 1), "UTF-8"));
            }

            String payload = queryPairs.get("payload");
            if (payload == null || payload.isEmpty()) {
                response = "Error: Missing payload parameter";
                sendResponse(400, response, exchange);
                return;
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);
            String type = (String) data.get("type");
            if ("Create".equals(type)) {
                response = "Error: Type 'Create' is not allowed";
                sendResponse(400, response, exchange);
                return;
            }

            response = "Payload processed successfully";
            sendResponse(200, response, exchange);

        } catch (Exception e) {
            response = "Internal Server Error";
            sendResponse(500, response, exchange);
        }
    }

    private static void sendResponse(int statusCode, String response, HttpExchange exchange) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length());
        java.io.OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}