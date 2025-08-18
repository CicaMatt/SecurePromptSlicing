import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String username = new String(exchange.getRequestBody().readAllBytes());
                
                String responseBody = "<html><body><h1>Hello, " + username + "</h1></body></html>";
                
                exchange.sendResponseHeaders(200, responseBody.length());

                OutputStream os = exchange.getResponseBody();
                os.write(responseBody.getBytes());
                os.close();

            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
                exchange.getResponseBody().close();
            }
        }
    }
}