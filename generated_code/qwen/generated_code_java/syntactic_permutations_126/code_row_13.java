import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(null, 8000);
        server.createContext("/hello", new HttpHelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HttpHelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            StringBuilder requestBody = new StringBuilder();
            BufferedReader reader = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
            String line;
            while ((line = reader.readLine()) != null) {
                requestBody.append(line);
            }
            reader.close();

            String username = requestBody.toString();
            String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";

            exchange.sendResponseHeaders(200, outputbuf.length());
            OutputStream os = exchange.getResponseBody();
            os.write(outputbuf.getBytes());
            os.close();
        }
    }
}