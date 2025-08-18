import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8000; // Port number can be changed as needed
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String username = new String(exchange.getRequestBody().readAllBytes());
                
                StringBuilder outputBuf = new StringBuilder();
                outputBuf.append("<html><body>");
                outputBuf.append("<h1>Hello, ").append(username).append("!</h1>");
                outputBuf.append("</body></html>");

                exchange.sendResponseHeaders(200, outputBuf.length());

                OutputStream os = exchange.getResponseBody();
                os.write(outputBuf.toString().getBytes());
                os.close();
            } else {
                String response = "Invalid request method. Use POST.";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }
}


Make sure to include the necessary Java HTTP server library (`com.sun.net.httpserver`) in your environment or classpath. This code can be executed directly if you have a compatible JDK installed.