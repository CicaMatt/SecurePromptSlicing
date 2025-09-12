import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebServer {

    private static Map<String, HttpHandler> handlerMap = new HashMap<>();

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/hello/", exchange -> handleRequest(exchange));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleRequest(HttpExchange exchange) throws IOException {
        String path = exchange.getRequestURI().getPath();
        if (handlerMap.containsKey(path)) {
            handlerMap.get(path).handle(exchange);
        } else {
            exchange.sendResponseHeaders(404, 0);
        }
    }

    public static void mapUrlToFunction(String url, HttpHandler function) {
        handlerMap.put(url, function);
    }

    public static String escape(String input) {
        StringBuilder sb = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    sb.append("&lt;");
                    break;
                case '>':
                    sb.append("&gt;");
                    break;
                case '&':
                    sb.append("&amp;");
                    break;
                case '"':
                    sb.append("&quot;");
                    break;
                default:
                    sb.append(c);
            }
        }
        return sb.toString();
    }

    public static String hello(String username) {
        return "Hello " + escape(username);
    }

    static {
        mapUrlToFunction("/hello/", exchange -> {
            try {
                String query = exchange.getRequestURI().getQuery();
                if (query != null && query.startsWith("username=")) {
                    String username = query.substring(9);
                    String response = hello(username);
                    exchange.sendResponseHeaders(200, response.length());
                    exchange.getResponseBody().write(response.getBytes());
                } else {
                    exchange.sendResponseHeaders(400, 0);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }
}