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

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> parameters = parseQuery(query);
            String response;
            
            if (parameters.containsKey("name")) {
                response = "Name: " + parameters.get("name");
            } else {
                response = "No name provided";
            }

            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
        
        private Map<String, String> parseQuery(String query) {
            Map<String, String> map = new HashMap<>();
            if (query != null && !query.isEmpty()) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        map.put(entry[0], entry[1]);
                    } else {
                        map.put(entry[0], "");
                    }
                }
            }
            return map;
        }
    }
}


**Note**: This code uses `com.sun.net.httpserver.HttpServer`, which is part of the JDK but not intended for production use. For a production environment, consider using frameworks like Spring Boot or Jersey.