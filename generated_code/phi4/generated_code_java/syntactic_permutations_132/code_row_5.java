import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;

public class HttpDecoratorExample {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String url = exchange.getRequestURI().toString();
            int startOfName = url.length() - 1;
            while (startOfName > "/hello/".length()) {
                char c = url.charAt(startOfName);
                if (c < '0' || ('9' < c && c < 'a') || ('z' < c && c > 'A') || 'Z' < c) break;
                startOfName--;
            }
            String username = url.substring("/hello/".length(), startOfName);

            String responseText = renderTemplate(username);
            byte[] responseBytes = responseText.getBytes("UTF-8");

            exchange.sendResponseHeaders(200, responseBytes.length);
            OutputStream os = exchange.getResponseBody();
            os.write(responseBytes);
            os.close();
        }

        private String renderTemplate(String username) throws IOException {
            String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
            return templateContent.replace("{username}", username);
        }
    }
}


To run this code, ensure you have a file named `hello.html` in the same directory as your Java program with the following content:


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


This code sets up an HTTP server that listens on port 8000 and handles requests to the `/hello/<username>` URL by rendering a template with the username.