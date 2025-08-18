import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;

public class HttpServerExample {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requestUri = exchange.getRequestURI().toString();
            String username = requestUri.replace("/hello/", "");

            if (username.isEmpty()) {
                username = "Guest";
            }

            String response = renderTemplate(username);
            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private String renderTemplate(String username) throws IOException {
            String templatePath = "hello.html";
            String templateContent = new String(Files.readAllBytes(Paths.get(templatePath)));
            return templateContent.replace("{username}", username);
        }
    }
}


Ensure you have a file named `hello.html` in the same directory as your Java program, with content similar to:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {username}!</h1>
</body>
</html>