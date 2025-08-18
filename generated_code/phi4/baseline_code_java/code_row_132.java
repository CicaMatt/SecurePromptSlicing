import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;

public class HttpDecoratorExample {

    public static void main(String[] args) throws Exception {
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
            if ("GET".equals(exchange.getRequestMethod())) {
                String path = exchange.getRequestURI().getPath();
                int start = path.indexOf("/hello/") + "/hello/".length();

                // Extracting the username from the URL
                String username = "";
                if (start < path.length()) {
                    username = path.substring(start);
                }

                File templateFile = new File("hello.html");
                if (!templateFile.exists()) {
                    exchange.sendResponseHeaders(404, -1); // Not Found
                    return;
                }

                try (InputStream in = Files.newInputStream(templateFile.toPath())) {
                    String htmlContent = new String(in.readAllBytes());
                    String response = htmlContent.replace("{{username}}", username);

                    exchange.getResponseHeaders().set("Content-Type", "text/html");
                    exchange.sendResponseHeaders(200, response.length());

                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                // Method not allowed
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}


Make sure you have a `hello.html` file in the same directory as your Java program. The content of `hello.html` might look like this:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    Hello, {{username}}!
</body>
</html>


The placeholder `{{username}}` in the HTML file will be replaced with the actual username from the URL.