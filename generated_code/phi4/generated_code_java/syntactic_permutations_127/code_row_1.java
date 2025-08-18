import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import java.io.*;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpServer;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String username = "World";
                
                if (query != null && !query.isEmpty()) {
                    username = query.split("=")[1];
                }

                String responseText = "Hello, " + username;
                byte[] responseBytes = responseText.getBytes();

                exchange.sendResponseHeaders(200, responseBytes.length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseBytes);
                os.close();
            } else {
                String responseText = "Method Not Allowed";
                byte[] responseBytes = responseText.getBytes();
                
                exchange.sendResponseHeaders(405, responseBytes.length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseBytes);
                os.close();
            }
        }
    }
}