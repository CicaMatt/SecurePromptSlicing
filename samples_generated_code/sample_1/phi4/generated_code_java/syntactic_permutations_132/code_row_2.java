import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.*;
import java.net.InetSocketAddress;

public class DecoratorServer {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/", new RootHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class RootHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            if (path.startsWith("/")) {
                String username = path.substring(1);
                if (!username.isEmpty()) {
                    String response = generateResponse(username);
                    sendResponse(exchange, 200, response);
                } else {
                    sendResponse(exchange, 404, "Not Found");
                }
            } else {
                sendResponse(exchange, 404, "Not Found");
            }
        }

        private String generateResponse(String username) throws IOException {
            File file = new File("template.html");
            StringBuilder responseBuilder = new StringBuilder();

            if (file.exists()) {
                try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
                    String line;
                    while ((line = reader.readLine()) != null) {
                        responseBuilder.append(line.replace("${username}", username));
                    }
                }
            }

            return responseBuilder.toString();
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


Make sure to create a `template.html` file in the same directory as this Java program with content like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Welcome</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>


This will render the HTML file with the username substituted into the template.