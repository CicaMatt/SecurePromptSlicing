import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String username = new String(exchange.getRequestBody().readAllBytes());
                
                String responseHtml = "<html><body>" +
                        "<h1>Hello, " + username + "!</h1>" +
                        "</body></html>";

                exchange.sendResponseHeaders(200, responseHtml.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseHtml.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }
}