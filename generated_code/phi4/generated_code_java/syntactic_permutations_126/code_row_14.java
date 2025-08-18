import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String username = "";
                try (var bodyInputStream = exchange.getRequestBody()) {
                    int availableBytes = bodyInputStream.available();
                    byte[] buffer = new byte[availableBytes];
                    int readBytesCount = bodyInputStream.read(buffer);
                    if (readBytesCount > 0) {
                        username = new String(buffer, 0, readBytesCount);
                    }
                }

                String outputBuf = "<html><body><h1>Hello, " + username + "</h1></body></html>";
                exchange.sendResponseHeaders(200, outputBuf.getBytes().length);

                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(outputBuf.getBytes());
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }
    }
}