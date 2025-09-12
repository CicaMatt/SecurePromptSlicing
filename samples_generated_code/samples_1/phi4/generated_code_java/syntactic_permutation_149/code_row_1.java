import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class Main {

    private static List<String> messages = new ArrayList<>();

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/post", new PostHandler());
        server.createContext("/", new RootHandler());

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class PostHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Scanner scanner = new Scanner(exchange.getRequestBody());
                String message = scanner.useDelimiter("\\A").next();
                messages.add(message);
                
                insertUserMessageInDB(message);

                String response = "Redirecting to /";
                exchange.sendResponseHeaders(303, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }

        private void insertUserMessageInDB(String message) {
            // Simulate database insertion logic here
            System.out.println("Inserted into DB: " + message);
        }
    }

    static class RootHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            StringBuilder response = new StringBuilder("<html><body>");
            response.append("<h1>Messages:</h1><ul>");

            for (String message : messages) {
                response.append("<li>").append(message).append("</li>");
            }

            response.append("</ul></body></html>");

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.toString().getBytes());
            os.close();
        }
    }
}