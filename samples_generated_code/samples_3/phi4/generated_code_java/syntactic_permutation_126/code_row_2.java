import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloPage {

    public static void main(String[] args) throws Exception {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String response = "<html><body>Hello, " + getRequestBody(exchange) + "!</body></html>";
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }

        private String getRequestBody(HttpExchange exchange) throws IOException {
            var body = new StringBuilder();
            try (var inputStream = exchange.getRequestBody()) {
                int data;
                while ((data = inputStream.read()) != -1) {
                    body.append((char) data);
                }
            }
            return body.toString().trim();
        }
    }
}