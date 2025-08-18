import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
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
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = new HashMap<>();
                
                for (String param : query.split("&")) {
                    String[] keyValue = param.split("=");
                    if (keyValue.length == 2) {
                        queryParams.put(keyValue[0], keyValue[1]);
                    }
                }

                String name = queryParams.getOrDefault("payload", "{}");
                try {
                    Map<String, Object> payloadMap = parseJsonToMap(name);
                    String responseText = "Name: " + (String) payloadMap.get("name");
                    
                    exchange.sendResponseHeaders(200, responseText.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                } catch (Exception e) {
                    String responseText = "Error processing request";
                    exchange.sendResponseHeaders(500, responseText.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                }
            } else {
                String responseText = "Method Not Allowed";
                exchange.sendResponseHeaders(405, responseText.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            }
        }

        private Map<String, Object> parseJsonToMap(String json) throws Exception {
            // Assuming a simple JSON structure for demonstration purposes
            // This is not a complete JSON parser and should be replaced with a real one like Jackson or Gson in production
            if (json.startsWith("{") && json.endsWith("}")) {
                Map<String, Object> map = new HashMap<>();
                String content = json.substring(1, json.length() - 1).trim();
                
                for (String pair : content.split(",")) {
                    String[] keyValue = pair.split(":");
                    if (keyValue.length == 2) {
                        String key = keyValue[0].trim().replace("\"", "");
                        String value = keyValue[1].trim().replace("\"", "");
                        map.put(key, value);
                    }
                }
                
                return map;
            } else {
                throw new IllegalArgumentException("Invalid JSON format");
            }
        }
    }
}