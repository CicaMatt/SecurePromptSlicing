import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/api", new ApiHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        
        System.out.println("Server started on port " + port);
    }

    static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> payloadMap = new HashMap<>();
            
            if (query != null && !query.isEmpty()) {
                for (String param : query.split("&")) {
                    String[] keyValue = param.split("=");
                    if (keyValue.length == 2) {
                        payloadMap.put(keyValue[0], keyValue[1]);
                    }
                }
            }

            String responseText = "Name: ";
            String name = payloadMap.getOrDefault("name", "Unknown");
            responseText += name;
            
            exchange.sendResponseHeaders(200, responseText.length());
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        }
    }
}


To run this code:
1. Make sure you have Java installed.
2. Save the code to a file named `WebApp.java`.
3. Compile it using: `javac WebApp.java`
4. Run it with: `java WebApp`
5. Test by navigating to `http://localhost:8000/api?name=YourName` in your web browser or using a tool like curl.