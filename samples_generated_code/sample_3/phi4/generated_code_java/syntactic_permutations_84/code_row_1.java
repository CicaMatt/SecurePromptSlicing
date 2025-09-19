import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
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
            String response = "";
            int statusCode = 200;

            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, Object> requestParams = parseQueryParameters(exchange.getRequestURI().getQuery());
                
                if (!requestParams.containsKey("payload")) {
                    response = "Error: Payload parameter is missing.";
                    statusCode = 400;
                } else {
                    String payload = (String) requestParams.get("payload");
                    
                    try {
                        Map<String, Object> yamlMap = parseYaml(payload);
                        
                        if ("Create".equals(yamlMap.get("type"))) {
                            response = "Error: Type is Create.";
                            statusCode = 400;
                        } else {
                            response = "Request processed successfully.";
                        }
                    } catch (Exception e) {
                        response = "Error parsing YAML payload.";
                        statusCode = 400;
                    }
                }
            } else {
                response = "Error: Only GET requests are supported.";
                statusCode = 405;
            }

            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Map<String, Object> parseQueryParameters(String query) {
            Map<String, Object> queryParams = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] pair = param.split("=");
                    if (pair.length > 1) {
                        queryParams.put(pair[0], pair[1]);
                    }
                }
            }
            return queryParams;
        }

        private Map<String, Object> parseYaml(String yamlStr) throws IOException {
            ObjectMapper objectMapper = new ObjectMapper(new YAMLFactory());
            return objectMapper.readValue(yamlStr, Map.class);
        }
    }
}