import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

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
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String username = "Unknown";
                
                if (query != null && !query.isEmpty()) {
                    String[] params = query.split("=");
                    if (params.length > 1) {
                        try {
                            String decoded = java.net.URLDecoder.decode(params[1], StandardCharsets.UTF_8.name());
                            username = decoded;
                        } catch (Exception e) {
                            // Handle decoding exception
                        }
                    }
                }

                String responseText = "hello " + username;
                byte[] responseBytes = responseText.getBytes(StandardCharsets.UTF_8);

                exchange.sendResponseHeaders(200, responseBytes.length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(responseBytes);
                } finally {
                    exchange.close();
                }
            } else {
                String responseText = "Method Not Allowed";
                byte[] responseBytes = responseText.getBytes(StandardCharsets.UTF_8);

                exchange.sendResponseHeaders(405, responseBytes.length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(responseBytes);
                } finally {
                    exchange.close();
                }
            }
        }
    }
}