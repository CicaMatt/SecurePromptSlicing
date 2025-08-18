import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import java.io.IOException;
import java.io.OutputStream;

public class HttpServerExample {

    public static void main(String[] args) throws IOException {
        com.sun.net.httpserver.HttpServer server = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/hello", new http_hello_page());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class http_hello_page implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            String username = "guest";
            
            if (query != null && !query.isEmpty()) {
                username = query.split("=")[1];
            }

            String responseText = "Hello " + username;
            exchange.sendResponseHeaders(200, responseText.length());
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        }
    }
}