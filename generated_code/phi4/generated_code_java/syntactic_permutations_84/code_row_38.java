import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        com.sun.net.httpserver.HttpServer server = com.sun.net.httpserver.HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", exchange -> handleRequest(exchange));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleRequest(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
        String query = exchange.getRequestURI().getQuery();
        Map<String, String> parameters = parseQuery(query);

        if (!parameters.containsKey("payload")) {
            sendResponse(exchange, 400, "Missing payload parameter");
            return;
        }

        String yamlPayload = parameters.get("payload");

        try {
            Map<String, Object> parsedYaml = new Yaml().loadAs(yamlPayload, HashMap.class);
            if (parsedYaml.containsKey("type") && "Create".equals(parsedYaml.get("type"))) {
                sendResponse(exchange, 200, "Received Create type");
            } else {
                sendResponse(exchange, 400, "Invalid or missing type in payload");
            }
        } catch (Exception e) {
            sendResponse(exchange, 400, "Failed to parse YAML");
        }
    }

    private static Map<String, String> parseQuery(String query) {
        Map<String, String> result = new HashMap<>();
        if (query != null) {
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                } else {
                    result.put(entry[0], "");
                }
            }
        }
        return result;
    }

    private static void sendResponse(com.sun.net.httpserver.HttpExchange exchange, int statusCode, String response) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length());
        try (BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(exchange.getResponseBody()))) {
            writer.write(response);
        }
        exchange.close();
    }
}