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
                Map<String, String> params = parseQuery(query);
                
                if (params != null && params.containsKey("payload")) {
                    try {
                        String payloadString = params.get("payload");
                        Map<String, String> payloadMap = parsePayload(payloadString);

                        String responseText;
                        if (payloadMap != null && payloadMap.containsKey("name")) {
                            responseText = "Name: " + payloadMap.get("name");
                        } else {
                            responseText = "Name not found";
                        }
                        
                        exchange.sendResponseHeaders(200, responseText.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(responseText.getBytes());
                        os.close();
                    } catch (Exception e) {
                        String responseText = "Invalid payload format";
                        exchange.sendResponseHeaders(400, responseText.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(responseText.getBytes());
                        os.close();
                    }
                } else {
                    String responseText = "Missing or invalid payload parameter";
                    exchange.sendResponseHeaders(400, responseText.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                }
            } else {
                String responseText = "Method Not Allowed";
                exchange.sendResponseHeaders(405, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            }
        }

        private Map<String, String> parseQuery(String query) {
            if (query == null || query.isEmpty()) return null;
            
            Map<String, String> params = new HashMap<>();
            String[] pairs = query.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                try {
                    params.put(pair.substring(0, idx), pair.substring(idx + 1));
                } catch (Exception e) {
                    // Ignore invalid parameter
                }
            }
            
            return params;
        }

        private Map<String, String> parsePayload(String payloadString) throws Exception {
            if (payloadString == null || payloadString.isEmpty()) throw new IllegalArgumentException("Empty payload");
            
            Map<String, String> payloadMap = new HashMap<>();
            // Assuming the payload is a simple key=value&key2=value2 format
            for (String pair : payloadString.split("&")) {
                int idx = pair.indexOf("=");
                if (idx != -1) {
                    String key = pair.substring(0, idx);
                    String value = pair.substring(idx + 1);
                    payloadMap.put(key, value);
                }
            }

            return payloadMap;
        }
    }
}