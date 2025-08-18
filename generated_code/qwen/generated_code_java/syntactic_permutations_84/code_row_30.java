import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/test", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> parameters = splitQuery(query);
            if (!parameters.containsKey("payload")) {
                sendResponse(exchange, "Error: Missing payload parameter", 400);
                return;
            }
            String payload = parameters.get("payload");
            if (payload.equals("Create")) {
                sendResponse(exchange, "Error: Payload type Create is not allowed", 400);
                return;
            }
            // If additional processing needed for other types of payloads, add here
            sendResponse(exchange, "Success", 200);
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            byte[] bytes = response.getBytes(StandardCharsets.UTF_8);
            exchange.sendResponseHeaders(statusCode, bytes.length);
            OutputStream os = exchange.getResponseBody();
            os.write(bytes);
            os.close();
        }

        private Map<String, String> splitQuery(String query) {
            return java.util.stream.Stream.of(query.split("&"))
                    .filter(param -> param.contains("="))
                    .collect(java.util.stream.Collectors.toMap(
                            param -> param.split("=")[0],
                            param -> param.split("=").length > 1 ? param.split("=")[1] : ""
                    ));
        }
    }
}