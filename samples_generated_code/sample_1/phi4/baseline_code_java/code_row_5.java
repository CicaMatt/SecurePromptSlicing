import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class HttpDecoratorExample {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            String username = path.substring(path.lastIndexOf('/') + 1);

            String response = renderTemplate(username);

            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private String renderTemplate(String username) throws IOException {
            String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
            return templateContent.replace("{username}", username);
        }
    }
}


Make sure you have a `hello.html` file in the same directory as this Java program with the following content:




This code sets up a simple HTTP server that listens on port 8080 and handles requests to the `/hello/<username>` URL. It reads the `hello.html` file, replaces `{username}` with the actual username from the URL, and returns the rendered HTML as the response.