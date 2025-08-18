import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            String username = "guest";
            
            if (query != null && !query.isEmpty()) {
                username = query.split("=")[1];
            }

            String responseText = "Hello, " + username;
            exchange.sendResponseHeaders(200, responseText.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        }
    }
}


This code sets up a simple HTTP server using Java's built-in `HttpServer`. It listens on port 8000 and responds to requests at the `/hello` endpoint. The handler extracts the username from the query parameters of the request URI and constructs a greeting message, which it sends back as an HTTP response.