import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HelloWorldDecorator {

    private static final String TEMPLATE_PATH = "hello.html";

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String path = exchange.getRequestURI().getPath();
                int startOfUserParam = path.lastIndexOf('/') + 1;
                int endOfUserParam = path.length();

                // Extract username from URL
                String username = (startOfUserParam < endOfUserParam) ? path.substring(startOfUserParam, endOfUserParam) : "Guest";

                // Read the template file content
                String templateContent = new String(Files.readAllBytes(Paths.get(TEMPLATE_PATH)));

                // Replace {{username}} in the template with actual username
                String responseContent = templateContent.replace("{{username}}", username);

                exchange.getResponseHeaders().set("Content-Type", "text/html");
                exchange.sendResponseHeaders(200, responseContent.getBytes().length);
                try (var os = exchange.getResponseBody()) {
                    os.write(responseContent.getBytes());
                }
            } else {
                sendMethodNotAllowed(exchange);
            }
        }

        private void sendMethodNotAllowed(HttpExchange exchange) throws IOException {
            String response = "Method Not Allowed";
            exchange.sendResponseHeaders(405, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


Make sure the `hello.html` file is in the same directory as your Java program and contains placeholders like `{{username}}`. For example:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{username}}!</h1>
</body>
</html>


Run the Java program and visit `http://localhost:8080/hello/YourName` in a web browser to see it in action.