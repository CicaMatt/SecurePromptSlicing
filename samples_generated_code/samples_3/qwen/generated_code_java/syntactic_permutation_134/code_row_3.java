import java.io.IOException;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleHttpServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requestPath = exchange.getRequestURI().getPath();
            String username = requestPath.substring("/hello/".length());
            username = URLDecoder.decode(username, StandardCharsets.UTF_8.toString());
            String response = hello(escape(username));
            exchange.sendResponseHeaders(200, response.getBytes().length);
            exchange.getResponseBody().write(response.getBytes());
            exchange.close();
        }

        private String hello(String username) {
            return "Hello " + username;
        }

        private String escape(String input) {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < input.length(); ++i) {
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