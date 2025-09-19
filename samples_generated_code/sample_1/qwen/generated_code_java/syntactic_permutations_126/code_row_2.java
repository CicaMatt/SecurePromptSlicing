import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(null, 8000);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String username = "";
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(exchange.getRequestBody()))) {
                StringBuilder bodyBuilder = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    bodyBuilder.append(line);
                }
                username = bodyBuilder.toString().trim();
            }

            String outputbuf = "<html><body>Hello, " + username + "!</body></html>";
            exchange.sendResponseHeaders(200, outputbuf.getBytes().length);

            try (OutputStream os = exchange.getResponseBody()) {
                os.write(outputbuf.getBytes());
            }
        }
    }
}