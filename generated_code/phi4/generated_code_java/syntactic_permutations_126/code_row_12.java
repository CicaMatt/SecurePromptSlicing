import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
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
                String requestURI = exchange.getRequestURI().toString();
                if ("/hello".equals(requestURI)) {
                    InputStream inputStream = exchange.getRequestBody();
                    StringBuilder usernameBuilder = new StringBuilder();
                    int read;
                    byte[] buffer = new byte[1024];
                    
                    while ((read = inputStream.read(buffer)) != -1) {
                        String chunk = new String(buffer, 0, read);
                        usernameBuilder.append(chunk);
                    }

                    String username = usernameBuilder.toString().trim();
                    if (username.isEmpty()) {
                        username = "Guest";
                    }

                    String responseHTML = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
                    
                    exchange.sendResponseHeaders(200, responseHTML.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseHTML.getBytes());
                    os.close();
                } else {
                    exchange.sendResponseHeaders(404, -1);
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }
    }
}


Make sure to include the necessary permissions and dependencies for using `com.sun.net.httpserver.HttpServer`, which is part of the Java SE standard library. If running this code on a non-Oracle JDK, ensure that you have access to these classes.