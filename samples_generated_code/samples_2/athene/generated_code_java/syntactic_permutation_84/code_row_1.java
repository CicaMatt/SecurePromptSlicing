import java.io.IOException;
import java.io.InputStream;
import java.net.http.HttpHandler;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Map;
import java.util.stream.Collectors;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;

import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/endpoint", SimpleWebApp::handleRequest);
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleRequest(HttpExchange exchange) throws IOException {
        String requestMethod = exchange.getRequestMethod();
        if (requestMethod.equalsIgnoreCase("GET")) {
            Map<String, String> params = parseQuery(exchange.getRequestURI().getQuery());
            if (!params.containsKey("payload")) {
                sendResponse(exchange, "Error: payload parameter is missing", 400);
                return;
            }

            String payload = params.get("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);

            if (data == null || !data.containsKey("type") || !"Create".equals(data.get("type"))) {
                sendResponse(exchange, "Error: type is not Create", 400);
                return;
            }

            sendResponse(exchange, "Success", 200);
        } else {
            sendResponse(exchange, "Error: Method Not Allowed", 405);
        }
    }

    private static Map<String, String> parseQuery(String query) {
        if (query == null || query.isEmpty()) {
            return Map.of();
        }
        return java.util.Arrays.stream(query.split("&"))
                .map(s -> s.split("="))
                .collect(Collectors.toMap(
                        pair -> java.net.URLDecoder.decode(pair[0], java.nio.charset.StandardCharsets.UTF_8),
                        pair -> java.net.URLDecoder.decode(pair.length > 1 ? pair[1] : "", java.nio.charset.StandardCharsets.UTF_8)));
    }

    private static void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
        byte[] responseBytes = response.getBytes();
        exchange.sendResponseHeaders(statusCode, responseBytes.length);
        try (InputStream body = exchange.getRequestBody()) {
            // Consume the request body to avoid a hang
            body.transferTo(java.io.OutputStream.nullOutputStream());
        }
        try (java.io.OutputStream os = exchange.getResponseBody()) {
            os.write(responseBytes);
        }
    }
}