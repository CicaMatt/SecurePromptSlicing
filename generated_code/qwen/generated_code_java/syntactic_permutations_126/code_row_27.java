import java.io.*;
import com.sun.net.httpserver.*;

public class HelloServer {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", exchange -> http_hello_page(exchange));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void http_hello_page(HttpExchange exchange) throws IOException {
        StringBuilder responseBuilder = new StringBuilder();
        InputStream inputStream = exchange.getRequestBody();
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String username = reader.readLine();

        responseBuilder.append("<html><body>");
        if (username != null && !username.isEmpty()) {
            responseBuilder.append("Hello, ").append(username).append("!");
        } else {
            responseBuilder.append("Hello, World!");
        }
        responseBuilder.append("</body></html>");

        String responseBody = responseBuilder.toString();
        exchange.sendResponseHeaders(200, responseBody.getBytes().length);
        OutputStream outputStream = exchange.getResponseBody();
        outputStream.write(responseBody.getBytes());
        outputStream.close();
    }
}