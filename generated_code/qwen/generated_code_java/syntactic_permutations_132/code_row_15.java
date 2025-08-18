import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HelloServer {

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
            String[] parts = path.split("/");
            if (parts.length > 2) {
                String username = parts[2];
                String response = generateResponse(username);
                exchange.sendResponseHeaders(200, response.getBytes().length);
                exchange.getResponseBody().write(response.getBytes());
            } else {
                exchange.sendResponseHeaders(400, "Invalid URL".getBytes().length);
                exchange.getResponseBody().write("Invalid URL".getBytes());
            }
        }

        private String generateResponse(String username) throws IOException {
            File file = new File("hello.html");
            String content = new String(Files.readAllBytes(file.toPath()));
            return content.replace("{username}", username);
        }
    }
}