import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class HttpDecoratorExample {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        Pattern pattern = Pattern.compile("/hello/(.*)");
        server.createContext("/", new HelloHandler(pattern));
        
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class HelloHandler implements HttpHandler {
        private final Pattern pattern;

        public HelloHandler(Pattern pattern) {
            this.pattern = pattern;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            Matcher matcher = pattern.matcher(exchange.getRequestURI().toString());
            if (matcher.matches()) {
                String username = matcher.group(1);
                String response = renderTemplate(username);
                
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                sendNotFound(exchange);
            }
        }

        private String renderTemplate(String username) throws IOException {
            String template = new String(Files.readAllBytes(Paths.get("hello.html")));
            return template.replace("{username}", username);
        }

        private void sendNotFound(HttpExchange exchange) throws IOException {
            String response = "Not Found";
            exchange.sendResponseHeaders(404, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
