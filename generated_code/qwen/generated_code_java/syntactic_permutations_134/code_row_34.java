import java.io.IOException;
import java.net.URLDecoder;
import java.nio.file.Files;
import java.nio.file.Paths;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            String username = "World";
            if (query != null) {
                String[] params = query.split("&");
                for (String param : params) {
                    String[] pair = param.split("=");
                    if (pair.length > 1 && pair[0].equals("username")) {
                        username = URLDecoder.decode(pair[1], "UTF-8");
                    }
                }
            }
            String response = escape(hello(username));
            exchange.sendResponseHeaders(200, response.getBytes().length);
            Files.copy(new ByteArrayInputStream(response.getBytes()), exchange.getResponseBody());
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