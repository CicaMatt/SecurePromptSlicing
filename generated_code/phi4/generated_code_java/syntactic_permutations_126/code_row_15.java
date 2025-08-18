import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                String username = exchange.getRequestURI().getQuery().split("=")[1];
                
                String responseBody = "<html><body>"
                        + "<h1>Hello, " + username + "!</h1>"
                        + "</body></html>";

                byte[] outputBytes = responseBody.getBytes();
                exchange.sendResponseHeaders(200, outputBytes.length);
                OutputStream os = exchange.getResponseBody();
                os.write(outputBytes);
                os.close();
            }
        });
        
        server.setExecutor(null); // creates a default executor
        server.start();

        System.out.println("Server is listening on port 8000");
    }
}


Make sure to include the `com.sun.net.httpserver.HttpServer` library in your classpath. This code sets up a basic HTTP server that listens for requests at `/hello`. It extracts the username from the query parameters and returns an HTML response greeting the user by name.