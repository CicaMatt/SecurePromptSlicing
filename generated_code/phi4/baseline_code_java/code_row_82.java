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
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requestMethod = exchange.getRequestMethod();

            if ("GET".equalsIgnoreCase(requestMethod)) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = parseQuery(query);

                String nameValue = "Unknown";
                if (queryParams.containsKey("payload")) {
                    try {
                        Map<String, Object> payloadMap = new ObjectMapper().readValue(queryParams.get("payload"), HashMap.class);
                        if (payloadMap.containsKey("name")) {
                            nameValue = payloadMap.get("name").toString();
                        }
                    } catch (Exception e) {
                        // Handle JSON parsing exception
                    }
                }

                String response = "Name: " + nameValue;
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, String> parseQuery(String query) {
            if (query == null || query.isEmpty()) {
                return new HashMap<>();
            }
            Map<String, String> result = new HashMap<>();
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                } else {
                    result.put(entry[0], "");
                }
            }
            return result;
        }

    }
}


Note: This code uses `com.sun.net.httpserver.HttpServer` which is part of the JDK but not intended for production use. For a real-world application, consider using frameworks like Spring Boot or Jakarta EE. The JSON parsing relies on Jackson's `ObjectMapper`, so you need to include this dependency in your project:


<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.15.0</version>
</dependency>


Make sure to add the above Maven dependency if you are using a build tool like Maven.