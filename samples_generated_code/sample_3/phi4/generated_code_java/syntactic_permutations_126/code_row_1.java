import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HelloHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                if ("POST".equals(exchange.getRequestMethod())) {
                    var requestBody = new byte[exchange.getRequestBody().available()];
                    exchange.getRequestBody().read(requestBody);

                    String username = new String(requestBody).trim();
                    String responseHtml = "<html><body><h1>Hello, " + username + "!</h1></body></html>";

                    exchange.sendResponseHeaders(200, responseHtml.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseHtml.getBytes());
                    os.close();
                } else {
                    exchange.sendResponseHeaders(405, -1); // Method Not Allowed
                }
            }
        });

        server.setExecutor(null);
        server.start();
    }
}
