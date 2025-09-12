import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                String username = null;
                if (exchange.getRequestMethod().equalsIgnoreCase("POST")) {
                    try (var in = exchange.getRequestBody()) {
                        byte[] buffer = new byte[1024];
                        int length = in.read(buffer);
                        username = new String(buffer, 0, length).trim();
                    }
                }

                String response = "<html><body><h1>Hello " + 
                                  (username != null ? username : "World") + "</h1></body></html>";

                exchange.sendResponseHeaders(200, response.length());
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        });

        server.setExecutor(null);
        server.start();
    }
}


Make sure you have the necessary libraries in your classpath to run this code. This example uses `com.sun.net.httpserver`, which is part of the standard Java library but might not be available in all environments or versions.