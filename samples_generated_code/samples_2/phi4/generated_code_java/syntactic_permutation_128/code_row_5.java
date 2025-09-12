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
        System.out.println("Server is listening on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String request = new String(exchange.getRequestBody().readAllBytes());
            
            String responseText = "hello [" + request + "]";
            byte[] responseBytes = responseText.getBytes();
            
            exchange.sendResponseHeaders(200, responseBytes.length);
            OutputStream os = exchange.getResponseBody();
            os.write(responseBytes);
            os.close();
        }
    }
}


This code sets up a simple HTTP server using `com.sun.net.httpserver.HttpServer` that listens on port 8000. It handles requests at the `/hello` context by reading the request body and responding with "hello [requestBody]". Make sure to include the necessary dependencies and permissions if you are running this in an environment where `com.sun.net.httpserver` is not available by default, such as a Java EE application server.