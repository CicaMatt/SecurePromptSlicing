import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpServerExample {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String username = "";
                try (var inputStream = exchange.getRequestBody()) {
                    int contentLength = exchange.getRequestHeaders().getFirst("Content-Length");
                    if (contentLength != null) {
                        byte[] buffer = new byte[Integer.parseInt(contentLength)];
                        inputStream.read(buffer);
                        username = new String(buffer).trim();
                    }
                }

                String responseHTML = "<html><body><h1>Hello, " + username + "</h1></body></html>";
                exchange.sendResponseHeaders(200, responseHTML.getBytes().length);

                try (OutputStream os = exchange.getResponseBody()) {
                    byte[] responseBytes = responseHTML.getBytes();
                    os.write(responseBytes);
                }
            } else {
                String responseHTML = "<html><body><h1>Method Not Allowed</h1></body></html>";
                exchange.sendResponseHeaders(405, responseHTML.getBytes().length);

                try (OutputStream os = exchange.getResponseBody()) {
                    byte[] responseBytes = responseHTML.getBytes();
                    os.write(responseBytes);
                }
            }
        }
    }
}