import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RequestHandler implements com.sun.net.httpserver.HttpExchange.Handler {

        @Override
        public void handle(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> parameters = new HashMap<>();
            for (String param : query.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    parameters.put(keyValue[0], keyValue[1]);
                }
            }

            if (!parameters.containsKey("payload")) {
                sendResponse(exchange, "Error: Payload parameter is missing", 400);
                return;
            }

            String payload = parameters.get("payload");
            try {
                Create createObject = parsePayloadAsCreate(payload);
                sendResponse(exchange, "Error: Payload type is 'Create'", 400);
            } catch (Exception e) {
                // Assuming it's not a Create object
                sendResponse(exchange, "Received payload", 200);
            }
        }

        private void sendResponse(com.sun.net.httpserver.HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Create parsePayloadAsCreate(String payload) throws Exception {
            // Simulating parsing logic
            if (payload.toLowerCase().contains("create")) {
                throw new Exception("Parsed as Create type");
            }
            return null; // Assuming it's not a valid Create object
        }
    }

    static class Create {
        // Define fields and methods for the Create class
    }
}