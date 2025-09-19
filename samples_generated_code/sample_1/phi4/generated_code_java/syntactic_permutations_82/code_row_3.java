import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/get", new PayloadHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class PayloadHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = parseQuery(query);
                
                if (queryParams.containsKey("payload")) {
                    try {
                        Map<String, Object> payloadMap = loadPayloadIntoDictionary(queryParams.get("payload"));
                        if (payloadMap != null && payloadMap.containsKey("name")) {
                            String response = (String) payloadMap.get("name");
                            exchange.sendResponseHeaders(200, response.getBytes().length);
                            OutputStream os = exchange.getResponseBody();
                            os.write(response.getBytes());
                            os.close();
                        } else {
                            sendError(exchange, 400, "Name not found in payload");
                        }
                    } catch (Exception e) {
                        sendError(exchange, 500, "Failed to process request");
                    }
                } else {
                    sendError(exchange, 400, "Payload parameter missing");
                }
            } else {
                sendError(exchange, 405, "Method Not Allowed");
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> queryParams = new HashMap<>();
            if (query != null) {
                StringTokenizer tokenizer = new StringTokenizer(query, "&");
                while (tokenizer.hasMoreTokens()) {
                    String param = tokenizer.nextToken();
                    int idx = param.indexOf("=");
                    queryParams.put(param.substring(0, idx), param.substring(idx + 1));
                }
            }
            return queryParams;
        }

        private Map<String, Object> loadPayloadIntoDictionary(String payload) throws Exception {
            // Assuming the payload is a simple key-value pair in URL encoded format
            Map<String, String> map = parseQuery(payload);
            Map<String, Object> dictionary = new HashMap<>();
            for (Map.Entry<String, String> entry : map.entrySet()) {
                dictionary.put(entry.getKey(), entry.getValue());
            }
            return dictionary;
        }

        private void sendError(HttpExchange exchange, int statusCode, String message) throws IOException {
            String response = message;
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
