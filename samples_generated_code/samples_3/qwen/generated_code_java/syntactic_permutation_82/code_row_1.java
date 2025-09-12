import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                InputStream inputStream = exchange.getRequestBody();
                String body = new Scanner(inputStream, StandardCharsets.UTF_8.name()).useDelimiter("\\A").next();

                Map<String, String> payload = parseJsonToMap(body);
                String nameValue = payload.get("name");

                String response = nameValue != null ? nameValue : "";
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }

        private Map<String, String> parseJsonToMap(String json) {
            Map<String, String> map = new HashMap<>();
            if (json != null && !json.isEmpty()) {
                json = json.substring(1, json.length() - 1);
                String[] entries = json.split(",\\s*");
                for (String entry : entries) {
                    int sepIndex = entry.indexOf(':');
                    String key = entry.substring(0, sepIndex).replace("\"", "");
                    String value = entry.substring(sepIndex + 1).replace("\"", "");
                    map.put(key, value);
                }
            }
            return map;
        }
    }
}