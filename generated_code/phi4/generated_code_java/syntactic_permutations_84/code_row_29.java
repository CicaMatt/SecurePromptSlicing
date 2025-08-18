import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RequestHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> queryParams = parseQuery(query);

            if (!queryParams.containsKey("payload")) {
                sendResponse(exchange, 400, "Error: 'payload' parameter is missing.");
                return;
            }

            try {
                String payload = queryParams.get("payload");
                ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
                Map<String, Object> yamlData = mapper.readValue(payload, Map.class);

                if ("Create".equals(yamlData.get("type"))) {
                    sendResponse(exchange, 400, "Error: 'Create' type is not allowed.");
                } else {
                    sendResponse(exchange, 200, "Request processed successfully.");
                }
            } catch (Exception e) {
                sendResponse(exchange, 500, "Internal Server Error");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> queryParams = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] pair = param.split("=");
                    if (pair.length > 1) {
                        queryParams.put(pair[0], pair[1]);
                    } else {
                        queryParams.put(pair[0], "");
                    }
                }
            }
            return queryParams;
        }
    }
}