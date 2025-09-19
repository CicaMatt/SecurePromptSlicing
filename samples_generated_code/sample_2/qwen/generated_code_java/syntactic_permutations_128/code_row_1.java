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
        InputStream inputStream = exchange.getRequestBody();
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String query = reader.readLine();

        String[] parts = query.split("=");
        String username = parts.length > 1 ? parts[1] : "Guest";

        String response = "hello " + username;
        exchange.sendResponseHeaders(200, response.getBytes().length);
        OutputStream outputStream = exchange.getResponseBody();
        outputStream.write(response.getBytes());
        outputStream.close();
    }
}