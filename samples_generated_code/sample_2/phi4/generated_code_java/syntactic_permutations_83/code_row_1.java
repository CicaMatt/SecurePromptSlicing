import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/checkName", new NameHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class NameHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equalsIgnoreCase(exchange.getRequestMethod())) {
                InputStreamReader isr = new InputStreamReader(exchange.getRequestBody());
                BufferedReader br = new BufferedReader(isr);
                String jsonPayload = br.readLine();

                Map<String, Object> payloadMap = parseJson(jsonPayload);

                if (payloadMap.containsKey("name")) {
                    String response = "Name: " + payloadMap.get("name");
                    exchange.sendResponseHeaders(200, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                } else {
                    String response = "Field 'name' not found.";
                    exchange.sendResponseHeaders(400, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, Object> parseJson(String json) {
            Map<String, Object> map = new HashMap<>();
            if (json != null && !json.isEmpty()) {
                String[] pairs = json.split(",");
                for (String pair : pairs) {
                    int idx = pair.indexOf(":");
                    if (idx > 0) {
                        String key = pair.substring(1, idx).trim().replace("\"", "");
                        String value = pair.substring(idx + 1).trim().replace("\"", "");
                        map.put(key, value);
                    }
                }
            }
            return map;
        }
    }
}


This code sets up a simple HTTP server using Java's built-in `HttpServer` class. It listens on port 8000 and checks for the field "name" in a JSON payload sent via POST requests to `/checkName`. If the field exists, it returns its value; otherwise, it sends an error response. The JSON parsing is basic and assumes a simple key-value structure without nested objects or arrays.