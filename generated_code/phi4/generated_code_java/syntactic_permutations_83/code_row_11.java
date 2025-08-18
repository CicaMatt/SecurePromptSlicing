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
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/payload", new PayloadHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class PayloadHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> payload = readPayload(exchange);
                String response = payload.getOrDefault("name", "Field 'name' not found");
                sendResponse(exchange, 200, response);
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private Map<String, String> readPayload(HttpExchange exchange) throws IOException {
            Map<String, String> payload = new HashMap<>();
            try (var inputStream = exchange.getRequestBody()) {
                var content = new byte[exchange.getRequestHeaders().getFirst("Content-Length").getBytes()];
                int bytesRead = inputStream.read(content);
                if (bytesRead > 0) {
                    String body = new String(content, "UTF-8");
                    for (String param : body.split("&")) {
                        String[] keyValue = param.split("=");
                        if (keyValue.length == 2) {
                            payload.put(keyValue[0], keyValue[1]);
                        }
                    }
                }
            }
            return payload;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


To run the above code:
1. Save it in a file named `WebApp.java`.
2. Compile it using `javac WebApp.java`.
3. Run it with `java -cp .:lib/httpserver.jar WebApp` (assuming you have `httpserver.jar` from JDK's internal package or similar).
4. Test the application by sending a POST request to `http://localhost:8000/payload` with payload data, e.g., using tools like Postman or curl: 


curl -X POST http://localhost:8000/payload -d "name=John Doe"