import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import java.io.IOException;
import java.io.OutputStream;

public class HttpServerExample {

    public static void main(String[] args) throws IOException {
        var server = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String username = new java.util.Scanner(exchange.getRequestBody()).useDelimiter("\\A").next();
                
                String outputbuf = "Hello, " + username;
                
                exchange.sendResponseHeaders(200, outputbuf.length());
                OutputStream os = exchange.getResponseBody();
                os.write(outputbuf.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }
    }
}