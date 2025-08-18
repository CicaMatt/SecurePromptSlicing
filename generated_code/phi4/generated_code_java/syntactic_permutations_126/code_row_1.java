import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int serverPort = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(serverPort), 0);
        
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server is listening on port " + serverPort);
    }
}

class HelloHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        if ("POST".equals(exchange.getRequestMethod())) {
            String username = new String(exchange.getRequestBody().readAllBytes());
            
            String outputBuf = "<html><body>" +
                               "<h1>Hello, " + username + "</h1>" +
                               "</body></html>";

            exchange.sendResponseHeaders(200, outputBuf.length());

            OutputStream os = exchange.getResponseBody();
            os.write(outputBuf.getBytes());
            os.close();
        } else {
            String response = "Method Not Allowed";
            exchange.sendResponseHeaders(405, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}