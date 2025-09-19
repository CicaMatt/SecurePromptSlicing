import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if (!exchange.getRequestMethod().equalsIgnoreCase("GET")) {
                sendResponse(exchange, 405, "Method Not Allowed");
                return;
            }
            
            String path = exchange.getRequestURI().getPath();
            int index = path.indexOf("/", 7);
            String username = (index != -1) ? path.substring(7, index) : "";
            
            if (username.isEmpty()) {
                sendResponse(exchange, 404, "User Not Found");
                return;
            }
            
            String response = generateHelloPage(username);
            sendResponse(exchange, 200, response);
        }

        private String generateHelloPage(String username) throws IOException {
            String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
            return templateContent.replace("{username}", username);
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


Make sure you have a file named `hello.html` in the same directory as your Java program. The content of `hello.html` should be something like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    Hello, {username}!
</body>
</html>


Replace `{username}` with the actual username in your Java code.