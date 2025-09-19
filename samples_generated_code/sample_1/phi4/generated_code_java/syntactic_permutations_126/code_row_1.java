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
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equalsIgnoreCase(exchange.getRequestMethod())) {
                String username = new String(exchange.getRequestBody().readAllBytes());
                
                String responseHtml = "<html><body>" +
                        "<h1>Hello, " + username + "</h1>" +
                        "</body></html>";

                exchange.sendResponseHeaders(200, responseHtml.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseHtml.getBytes());
                os.close();
            } else {
                String responseHtml = "<html><body>" +
                        "<form method='POST'>" +
                        "Username: <input type='text' name='username'><br>" +
                        "<input type='submit' value='Submit'>" +
                        "</form>" +
                        "</body></html>";

                exchange.sendResponseHeaders(200, responseHtml.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseHtml.getBytes());
                os.close();
            }
        }
    }
}