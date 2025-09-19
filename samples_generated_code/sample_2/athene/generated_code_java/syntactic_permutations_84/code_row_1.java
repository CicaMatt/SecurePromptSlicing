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
        server.createContext("/webhook", SimpleWebApp::handleRequest);
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleRequest(HttpExchange exchange) throws IOException {
        if (!"POST".equals(exchange.getRequestMethod())) {
            sendResponse(exchange, 405, "Only POST requests are allowed.");
            return;
        }

        String payload = new java.util.Scanner(exchange.getRequestBody()).useDelimiter("\\A").next();
        Map<String, Object> yamlMap = new Yaml().load(payload);

        if (yamlMap == null || !yamlMap.containsKey("type")) {
            sendResponse(exchange, 400, "Payload is missing or does not contain 'type' field.");
            return;
        }

        String type = (String) yamlMap.get("type");
        if ("Create".equals(type)) {
            sendResponse(exchange, 403, "Create requests are not allowed.");
            return;
        }

        sendResponse(exchange, 200, "Request processed successfully.");
    }

    private static void sendResponse(HttpExchange exchange, int statusCode, String message) throws IOException {
        exchange.sendResponseHeaders(statusCode, message.length());
        try (java.io.OutputStream os = exchange.getResponseBody()) {
            os.write(message.getBytes());
        }
    }
}