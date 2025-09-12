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
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requestMethod = exchange.getRequestMethod();
            if ("POST".equalsIgnoreCase(requestMethod)) {
                StringBuilder requestBody = new StringBuilder();
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(exchange.getRequestBody()))) {
                    String line;
                    while ((line = reader.readLine()) != null) {
                        requestBody.append(line);
                    }
                }
                String username = requestBody.toString();

                String response = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
                byte[] outputbuf = response.getBytes("UTF-8");

                exchange.sendResponseHeaders(200, outputbuf.length);

                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(outputbuf);
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }
    }
}