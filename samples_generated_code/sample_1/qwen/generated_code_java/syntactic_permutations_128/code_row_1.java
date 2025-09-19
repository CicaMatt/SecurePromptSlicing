import java.io.*;
import com.sun.net.httpserver.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", exchange -> http_hello_page(exchange));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void http_hello_page(HttpExchange exchange) throws IOException {
        InputStream is = exchange.getRequestBody();
        StringBuilder textBuilder = new StringBuilder();
        try (Reader reader = new BufferedReader(new InputStreamReader(is, java.nio.charset.StandardCharsets.UTF_8))) {
            int c;
            while ((c = reader.read()) != -1) {
                textBuilder.append((char) c);
            }
        }

        String requestText = textBuilder.toString();
        String[] parts = requestText.split("=");
        String username = "Guest";
        if (parts.length > 1) {
            username = parts[1];
        }

        String response = "hello " + username;
        exchange.sendResponseHeaders(200, response.getBytes().length);
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}