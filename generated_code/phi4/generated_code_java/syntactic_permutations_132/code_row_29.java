import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;

public class HttpServerExample {

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
            if (path.matches("^/hello/.+$")) {
                String username = path.split("/")[2];
                String response = renderHelloTemplate(username);
                
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Not Found";
                exchange.sendResponseHeaders(404, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private String renderHelloTemplate(String username) throws IOException {
            String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
            return templateContent.replace("${username}", username);
        }
    }
}


Ensure you have a file named `hello.html` in the same directory as this Java program, containing content like:




This code sets up a simple HTTP server that listens for requests on port 8000. When someone visits `/hello/<username>`, it replaces `${username}` in `hello.html` with the actual username and sends it back as an HTTP response.