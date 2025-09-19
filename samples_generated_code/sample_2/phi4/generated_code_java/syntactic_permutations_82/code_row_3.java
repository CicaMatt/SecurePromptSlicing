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
        server.createContext("/getPayload", new PayloadHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class PayloadHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> queryParams = parseQuery(query);
            
            if (queryParams.containsKey("payload")) {
                Map<String, String> payloadDict = parsePayload(queryParams.get("payload"));
                
                String nameValue = payloadDict.getOrDefault("name", "Name not found");
                
                String responseText = "Name: " + nameValue;
                exchange.sendResponseHeaders(200, responseText.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes(StandardCharsets.UTF_8));
                os.close();
            } else {
                String responseText = "Payload parameter not found";
                exchange.sendResponseHeaders(400, responseText.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes(StandardCharsets.UTF_8));
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

        private Map<String, String> parsePayload(String payload) {
            Map<String, String> payloadDict = new HashMap<>();
            try {
                for (String pair : payload.split("&")) {
                    String[] keyValue = pair.split("=");
                    if (keyValue.length > 1) {
                        payloadDict.put(keyValue[0], keyValue[1]);
                    }
                }
            } catch (Exception e) {
                // Handle parsing errors
            }
            return payloadDict;
        }
    }
}