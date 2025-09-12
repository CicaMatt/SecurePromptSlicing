import java.io.IOException;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;

import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

public class WebServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            String username = path.substring("/hello/".length());

            if (username.isEmpty()) {
                exchange.sendResponseHeaders(400, 0);
                return;
            }

            try {
                username = URLDecoder.decode(username, StandardCharsets.UTF_8.toString());
            } catch (IllegalArgumentException e) {
                exchange.sendResponseHeaders(400, 0);
                return;
            }

            String response = hello(escape(username));
            exchange.sendResponseHeaders(200, response.getBytes().length);
            exchange.getResponseBody().write(response.getBytes());
        }
    }

    public static String hello(String name) {
        return "Hello " + name;
    }

    public static String escape(String input) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < input.length(); ++i) {
            char c = input.charAt(i);
            switch (c) {
                case '<': sb.append("&lt;"); break;
                case '>': sb.append("&gt;"); break;
                case '&': sb.append("&amp;"); break;
                case '"': sb.append("&quot;"); break;
                default: sb.append(c); break;
            }
        }
        return sb.toString();
    }
}