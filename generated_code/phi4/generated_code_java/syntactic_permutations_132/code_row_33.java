import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;

public class HelloDecorator {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/hello/", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if (exchange.getRequestMethod().equalsIgnoreCase("GET")) {
                String requestUri = exchange.getRequestURI().toString();
                int usernameStartIndex = requestUri.lastIndexOf('/') + 1;
                String username = requestUri.substring(usernameStartIndex);

                String response = renderTemplate(username);
                
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private String renderTemplate(String username) throws IOException {
            File file = new File("hello.html");
            BufferedReader br = null;
            StringBuilder sb = new StringBuilder();

            if (file.exists()) {
                br = new BufferedReader(new FileReader(file));
                String line;

                while ((line = br.readLine()) != null) {
                    sb.append(line.replace("{username}", username)).append("\n");
                }
            }

            return sb.toString();
        }
    }
}


Make sure you have a file named `hello.html` in the same directory as your Java program with content like:




This code sets up a simple HTTP server using `com.sun.net.httpserver.HttpServer` and handles requests to URLs of the form `/hello/<username>`. It reads an HTML template file and replaces `{username}` with the actual username from the URL.