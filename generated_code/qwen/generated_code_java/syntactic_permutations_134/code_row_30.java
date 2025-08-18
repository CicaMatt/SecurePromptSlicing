import java.io.IOException;
import java.net.URI;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class DecoratorExample {

    private static final Map<String, HttpHandler> urlToFunctionMap = new HashMap<>();

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        createMapping("/username", (exchange) -> {
            String query = exchange.getRequestURI().getQuery();
            if (query != null && query.contains("username=")) {
                String username = query.split("=")[1];
                String response = "Hello " + escape(username);
                exchange.sendResponseHeaders(200, response.getBytes().length);
                exchange.getResponseBody().write(response.getBytes());
            } else {
                exchange.sendResponseHeaders(400, -1); // Bad Request
            }
        });

        server.createContext("/username", urlToFunctionMap.get("/username"));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    public static void createMapping(String url, HttpHandler function) {
        urlToFunctionMap.put(url, function);
    }

    private static String escape(String input) {
        return URLEncoder.encode(input, StandardCharsets.UTF_8.toString());
    }
}