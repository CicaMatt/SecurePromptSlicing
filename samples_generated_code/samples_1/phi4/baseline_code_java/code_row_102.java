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
        server.createContext("/checkName", new NameHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class NameHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> payload = parsePayload(exchange.getRequestBody());
                String response = "Name not found";

                if (payload.containsKey("name")) {
                    response = "Name: " + payload.get("name");
                }

                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, String> parsePayload(InputStream requestBody) throws IOException {
            BufferedReader reader = new BufferedReader(new InputStreamReader(requestBody));
            StringBuilder payloadBuilder = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                payloadBuilder.append(line);
            }
            
            // Assuming the payload is URL-encoded key-value pairs
            Map<String, String> payloadMap = new HashMap<>();
            String[] pairs = payloadBuilder.toString().split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                if (idx > 0) {
                    payloadMap.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
            
            return payloadMap;
        }
    }
}