import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UserDecorator {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/", new UserHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UserHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requestPath = exchange.getRequestURI().getPath();
            if (!requestPath.equals("/")) {
                String username = requestPath.substring(1);
                String response = renderTemplate(username);
                exchange.sendResponseHeaders(200, response.getBytes().length);
                exchange.getResponseBody().write(response.getBytes());
                exchange.close();
            } else {
                exchange.sendResponseHeaders(404, -1);
                exchange.close();
            }
        }

        private String renderTemplate(String username) throws IOException {
            String template = new String(Files.readAllBytes(Paths.get("template.html")));
            return template.replace("{username}", username);
        }
    }
}