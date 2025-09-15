import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;

public class HttpDecorator {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        // Define the hello handler
        server.createContext("/hello/", new HelloHandler());
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();

            if (path.matches("/hello/\\w+")) {
                String username = path.split("/")[2]; // Extract the username from /hello/<username>

                try (InputStream is = HelloHandler.class.getResourceAsStream("/templates/hello.html");
                     BufferedReader br = new BufferedReader(new InputStreamReader(is))) {

                    StringBuilder content = new StringBuilder();
                    String line;

                    while ((line = br.readLine()) != null) {
                        content.append(line).append(System.lineSeparator());
                    }

                    String responseContent = content.toString().replace("{{ username }}", username);

                    exchange.sendResponseHeaders(200, responseContent.length());

                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(responseContent.getBytes());
                    }
                } catch (IOException e) {
                    System.err.println("Error reading template file: " + e.getMessage());
                    String response = "Internal Server Error";
                    
                    exchange.sendResponseHeaders(500, response.length());

                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(response.getBytes());
                    }
                }

            } else {
                String response = "Not Found";

                exchange.sendResponseHeaders(404, response.length());

                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}
