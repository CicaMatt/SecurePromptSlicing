import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloServer {

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
            String response = "";
            if ("GET".equals(exchange.getRequestMethod())) {
                // Read username from query string
                String query = exchange.getRequestURI().getQuery();
                String username = "Guest";
                
                if (query != null && !query.isEmpty()) {
                    String[] params = query.split("=");
                    if (params.length > 1) {
                        username = params[1];
                    }
                }

                // Construct HTML response
                String outputBuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
                
                // Write the response body to the response stream
                exchange.sendResponseHeaders(200, outputBuf.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(outputBuf.getBytes());
                os.close(); // Close the response stream
            }
        }
    }
}
