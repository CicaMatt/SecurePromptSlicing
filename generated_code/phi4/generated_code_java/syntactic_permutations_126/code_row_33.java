import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server is listening on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equalsIgnoreCase(exchange.getRequestMethod())) {
                String username = new String(exchange.getRequestBody().readAllBytes());
                
                StringBuilder responseHtml = new StringBuilder();
                responseHtml.append("<html><body>");
                responseHtml.append("<h1>Hello, ").append(username).append("!</h1>");
                responseHtml.append("</body></html>");

                String responseString = responseHtml.toString();

                exchange.sendResponseHeaders(200, responseString.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseString.getBytes());
                os.close();
            } else {
                sendBadRequest(exchange);
            }
        }

        private void sendBadRequest(HttpExchange exchange) throws IOException {
            String response = "Bad Request";
            exchange.sendResponseHeaders(400, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
