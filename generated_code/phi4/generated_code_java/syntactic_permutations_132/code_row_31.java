import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;

public class Main {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            if (path.matches("/hello/([^/]*)")) {
                String username = path.split("/")[2];
                String response = renderTemplate("Hello, " + username);
                
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Not Found";
                exchange.sendResponseHeaders(404, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private String renderTemplate(String username) {
            StringBuilder templateContent;
            try (BufferedReader br = new BufferedReader(new FileReader("hello.html"))) {
                templateContent = new StringBuilder();
                String line;
                while ((line = br.readLine()) != null) {
                    templateContent.append(line);
                }
                return templateContent.toString().replace("{username}", username);
            } catch (IOException e) {
                System.err.println("Error reading hello.html: " + e.getMessage());
                return "Error loading content";
            }
        }
    }
}


Save this code in a file named `Main.java` and ensure there is an accompanying HTML template file named `hello.html`. The `hello.html` should contain the placeholder `{username}`, like so:




This setup will start a server on port 8000 and handle requests to `/hello/<username>`, replacing `{username}` in the `hello.html` template with the actual username provided in the URL.