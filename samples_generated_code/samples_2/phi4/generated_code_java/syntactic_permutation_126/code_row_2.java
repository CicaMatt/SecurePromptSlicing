import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HelloPageServer {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/hello", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                if ("POST".equals(exchange.getRequestMethod())) {
                    String username = new String(exchange.getRequestBody().readAllBytes());
                    
                    String responseContent = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
                    
                    exchange.sendResponseHeaders(200, responseContent.length());
                    
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseContent.getBytes());
                    os.close();
                } else {
                    exchange.sendResponseHeaders(405, -1); // Method Not Allowed
                }
            }
        });
        
        server.setExecutor(null);
        server.start();
        System.out.println("Server started on port 8080");
    }
}