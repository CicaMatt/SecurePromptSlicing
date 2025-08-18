import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server is listening on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String username = new String(exchange.getRequestBody().readAllBytes(), StandardCharsets.UTF_8).trim();
                
                String outputBuf =
                        "<html>" +
                                "<head><title>Hello Page</title></head>" +
                                "<body>" +
                                "<h1>Hello, " + username + "</h1>" +
                                "</body>" +
                                "</html>";
                
                exchange.sendResponseHeaders(200, outputBuf.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(outputBuf.getBytes());
                }
            } else {
                String response = "Method not supported";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}