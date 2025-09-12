import java.io.IOException;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "";
            if ("GET".equals(exchange.getRequestMethod())) {
                String path = exchange.getRequestURI().getPath();
                String[] parts = path.split("/");
                if (parts.length > 2) {
                    String username = URLDecoder.decode(parts[2], StandardCharsets.UTF_8.toString());
                    response = hello(escape(username));
                }
            }
            exchange.sendResponseHeaders(200, response.getBytes().length);
            exchange.getResponseBody().write(response.getBytes());
            exchange.close();
        }

        private String hello(String name) {
            return "Hello " + name;
        }

        private String escape(String input) {
            if (input == null) {
                return "";
            }
            StringBuilder sb = new StringBuilder(input.length() * 2);
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);
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
    }
}