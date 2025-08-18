import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }
    
    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> params = parseQuery(query);
            
            if (params.containsKey("payload")) {
                String payload = params.get("payload");
                
                // Assuming the payload is a dictionary-like string format: key1=value1&key2=value2...
                Map<String, String> dictionary = parsePayload(payload);
                
                String response;
                if (dictionary.containsKey("name")) {
                    response = "Name: " + dictionary.get("name");
                } else {
                    response = "Name not found";
                }
                
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Payload parameter missing";
                exchange.sendResponseHeaders(400, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, String> parseQuery(String query) {
            if (query == null || query.isEmpty()) return new HashMap<>();
            
            Map<String, String> params = new HashMap<>();
            for (String param : query.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length > 1) {
                    params.put(keyValue[0], keyValue[1]);
                }
            }
            return params;
        }

        private Map<String, String> parsePayload(String payload) {
            Map<String, String> dictionary = new HashMap<>();
            for (String param : payload.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length > 1) {
                    dictionary.put(keyValue[0], keyValue[1]);
                }
            }
            return dictionary;
        }
    }
}