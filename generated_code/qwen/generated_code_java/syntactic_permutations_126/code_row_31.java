import java.io.*;
import com.sun.net.httpserver.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", HttpHelloServer::http_hello_page);
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void http_hello_page(HttpExchange exchange) throws IOException {
        InputStream requestBody = exchange.getRequestBody();
        BufferedReader reader = new BufferedReader(new InputStreamReader(requestBody));
        String username = reader.readLine();

        String response = "<html><body>Hello, " + (username != null ? username : "Guest") + "!</body></html>";
        byte[] outputbuf = response.getBytes();

        exchange.sendResponseHeaders(200, outputbuf.length);
        OutputStream os = exchange.getResponseBody();
        os.write(outputbuf);
        os.close();
    }
}