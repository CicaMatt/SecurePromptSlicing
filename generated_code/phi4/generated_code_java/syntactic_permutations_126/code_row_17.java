import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/hello", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                String responseHtml = "<html><body><h1>Hello, World!</h1></body></html>";
                
                // Setting the response header content type to HTML
                exchange.getResponseHeaders().add("Content-Type", "text/html");
                
                OutputStream os = exchange.getResponseBody();
                os.write(responseHtml.getBytes());
                os.close();  // Closing the output stream after writing
                
            }
        });
        
        server.setExecutor(null);  // creates a default executor
        server.start();
    }
}


Make sure to include the necessary library in your classpath if you are using an IDE or build tool like Maven or Gradle. The `com.sun.net.httpserver` package is part of Java's standard library.