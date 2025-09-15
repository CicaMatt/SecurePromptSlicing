import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.OutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.nio.file.Files;
import java.net.InetSocketAddress;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DecoratorExample {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/hello/\\w+", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requestUri = exchange.getRequestURI().toString();
            
            Pattern pattern = Pattern.compile("/hello/(\\w+)");
            Matcher matcher = pattern.matcher(requestUri);
            
            if (matcher.matches()) {
                String username = matcher.group(1);

                // Read the template file
                File helloFile = new File("hello.html");
                String htmlTemplate;
                
                try (FileInputStream fis = new FileInputStream(helloFile)) {
                    byte[] data = new byte[(int) helloFile.length()];
                    fis.read(data);
                    htmlTemplate = new String(data);
                }

                // Replace the placeholder with the actual username
                String response = htmlTemplate.replace("<username>", username);

                exchange.sendResponseHeaders(200, response.getBytes().length);
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
    }
}
