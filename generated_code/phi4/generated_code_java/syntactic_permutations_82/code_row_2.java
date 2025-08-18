import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> queryParams = parseQuery(query);

            if (queryParams.containsKey("payload")) {
                try {
                    Map<String, String> payloadMap = parsePayload(queryParams.get("payload"));
                    String nameValue = payloadMap.getOrDefault("name", "Not Found");
                    byte[] responseBytes = ("{" + "\"name\":\"" + nameValue + "\"" + "}").getBytes();
                    
                    exchange.sendResponseHeaders(200, responseBytes.length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseBytes);
                    os.close();

                } catch (Exception e) {
                    String response = "{\"error\": \"Invalid payload\"}";
                    byte[] responseBytes = response.getBytes();

                    exchange.sendResponseHeaders(400, responseBytes.length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseBytes);
                    os.close();
                }
            } else {
                String response = "{\"error\": \"Payload parameter missing\"}";
                byte[] responseBytes = response.getBytes();

                exchange.sendResponseHeaders(400, responseBytes.length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseBytes);
                os.close();
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> queryParams = new HashMap<>();
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

        private Map<String, String> parsePayload(String payload) throws Exception {
            // Assuming payload is URL-encoded key-value pairs
            return parseQuery(payload);
        }
    }
}