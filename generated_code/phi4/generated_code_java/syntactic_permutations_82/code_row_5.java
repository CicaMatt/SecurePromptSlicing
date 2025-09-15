import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = parseQuery(query);

                String nameValue = "Name not found";
                if (queryParams.containsKey("payload")) {
                    try {
                        Map<String, String> payloadMap = parsePayload(queryParams.get("payload"));
                        nameValue = payloadMap.getOrDefault("name", "Name not found");
                    } catch (Exception e) {
                        nameValue = "Error parsing payload";
                    }
                }

                String response = nameValue;
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes(StandardCharsets.UTF_8));
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes(StandardCharsets.UTF_8));
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
                    } else {
                        queryParams.put(pair[0], "");
                    }
                }
            }
            return queryParams;
        }

        private Map<String, String> parsePayload(String payload) throws Exception {
            // Assuming the payload is a simple key=value&key2=value2 format
            Map<String, String> map = new HashMap<>();
            for (String param : payload.split("&")) {
                String[] pair = param.split("=");
                if (pair.length > 1) {
                    map.put(pair[0], pair[1]);
                } else {
                    map.put(pair[0], "");
                }
            }
            return map;
        }
    }
}
