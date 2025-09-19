import java.io.*;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

public class HttpDecorator {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
        server.createContext("/", (exchange -> {
            String response = "Welcome to the root page!";
            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }));

        server.setExecutor(null); // creates a default executor
        server.start();

        System.out.println("Server started on port " + port);
    }

    static class UserHandler implements HttpHandler {
        
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "";
            try {
                String username = exchange.getRequestURI().getPath().substring(1);
                
                // Read the template file
                File file = new File("template.html");
                BufferedReader br = new BufferedReader(new FileReader(file));
                StringBuilder sb = new StringBuilder();
                String line;
                while ((line = br.readLine()) != null) {
                    sb.append(line).append("\n");
                }
                br.close();

                // Replace placeholder with username
                response = sb.toString().replace("{{username}}", username);

            } catch (Exception e) {
                response = "Error handling request: " + e.getMessage();
            }

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}


Make sure to have a file named `template.html` in the same directory with content like:




This code sets up a simple HTTP server using `com.sun.net.httpserver.HttpServer` and binds the `UserHandler` to URLs of the form `/<username>`. The handler reads the template file `template.html`, replaces the `{{username}}` placeholder with the actual username from the URL, and sends the modified content back as a response.