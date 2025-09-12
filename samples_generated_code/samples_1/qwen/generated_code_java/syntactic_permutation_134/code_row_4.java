import java.io.*;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HelloWorldServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            String[] parts = path.split("/");
            if (parts.length > 2 && "hello".equals(parts[1])) {
                String username = URLDecoder.decode(parts[2], StandardCharsets.UTF_8.toString());
                String response = hello(username);
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(404, 0);
            }
        }

        private String escape(String input) {
            if (input == null) return "";
            StringBuilder sb = new StringBuilder(input.length() + 20);
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);
                switch (c) {
                    case '&':
                        sb.append("&amp;");
                        break;
                    case '<':
                        sb.append("&lt;");
                        break;
                    case '>':
                        sb.append("&gt;");
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

        private String hello(String username) {
            return "Hello, " + escape(username) + "!";
        }
    }
}