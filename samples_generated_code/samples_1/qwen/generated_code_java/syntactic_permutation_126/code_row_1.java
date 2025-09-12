import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HelloHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                http_hello_page(exchange);
            }
        });
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void http_hello_page(HttpExchange exchange) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
        String line;
        while ((line = br.readLine()) != null) {
            requestBody.append(line);
        }
        br.close();

        String username = requestBody.toString();
        String response = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
        
        exchange.sendResponseHeaders(200, response.getBytes().length);

        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}