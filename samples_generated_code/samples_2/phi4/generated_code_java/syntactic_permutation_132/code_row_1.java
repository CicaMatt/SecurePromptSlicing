import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class HelloWorldDecorator {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        Pattern pattern = Pattern.compile("/hello/(.*)");
        server.createContext("/", new RootHandler());
        server.createContext("/hello", new HelloHandler(pattern));
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RootHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Welcome to the Hello World Decorator! Visit /hello/<username> to see it in action.";
            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }

    static class HelloHandler implements HttpHandler {
        private final Pattern pattern;

        public HelloHandler(Pattern pattern) {
            this.pattern = pattern;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            Matcher matcher = pattern.matcher(path);
            
            if (matcher.matches()) {
                String username = matcher.group(1);
                String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
                
                String output = templateContent.replace("<%= username %>", username);

                exchange.sendResponseHeaders(200, output.length());
                OutputStream os = exchange.getResponseBody();
                os.write(output.getBytes());
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
