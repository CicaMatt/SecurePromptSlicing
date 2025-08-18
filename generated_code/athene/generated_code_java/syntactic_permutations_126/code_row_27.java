import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HelloWorldServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HttpHelloPage());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HttpHelloPage implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String username = new String(exchange.getRequestBody().readAllBytes(), "UTF-8");
            String response = "<html><body>Hello, " + username + "!</body></html>";
            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}