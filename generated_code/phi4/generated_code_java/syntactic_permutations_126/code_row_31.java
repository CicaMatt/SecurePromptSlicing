import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleHttpServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String username = exchange.getRequestURI().getQuery().split("=")[1];

                StringBuilder outputBuf = new StringBuilder();
                outputBuf.append("<html><body>");
                outputBuf.append("<h1>Hello, ").append(username).append("!</h1>");
                outputBuf.append("</body></html>");

                exchange.sendResponseHeaders(200, outputBuf.length());
                OutputStream os = exchange.getResponseBody();
                os.write(outputBuf.toString().getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }
    }
}