import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

public class HttpDecoratorExample {

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
            String path = exchange.getRequestURI().getPath();
            if (path.matches("/hello/\\w+")) {
                String username = path.split("/")[2];
                String response = renderHelloTemplate(username);
                
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Not Found";
                exchange.sendResponseHeaders(404, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private String renderHelloTemplate(String username) throws IOException {
            String template = new String(Files.readAllBytes(Paths.get("hello.html")));
            return template.replace("${username}", username);
        }
    }
}


Make sure you have a `hello.html` file in the same directory as your Java program with content like:


<!DOCTYPE html>
<html>
<head>
    <title>Hello</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>


This code sets up a simple HTTP server that listens on port 8000 and responds to requests at `/hello/<username>` with the contents of `hello.html`, substituting `${username}` with the actual username from the URL.