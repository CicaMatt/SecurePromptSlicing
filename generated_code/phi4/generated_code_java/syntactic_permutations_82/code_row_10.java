import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/process", new RequestHandler());
        server.setExecutor(null);
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class RequestHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> parameters = parseQuery(query);

                if (parameters.containsKey("payload")) {
                    String payload = parameters.get("payload");
                    Map<String, String> dataMap = loadPayloadIntoDictionary(payload);
                    
                    String nameValue = dataMap.getOrDefault("name", "Name not found");
                    sendResponse(exchange, 200, nameValue);
                } else {
                    sendResponse(exchange, 400, "Payload parameter missing");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length > 1) {
                        result.put(entry[0], entry[1]);
                    } else {
                        result.put(entry[0], "");
                    }
                }
            }
            return result;
        }

        private Map<String, String> loadPayloadIntoDictionary(String payload) {
            Map<String, String> dataMap = new HashMap<>();
            for (String pair : payload.split("&")) {
                String[] keyValue = pair.split("=");
                if (keyValue.length > 1) {
                    dataMap.put(keyValue[0], keyValue[1]);
                } else {
                    dataMap.put(keyValue[0], "");
                }
            }
            return dataMap;
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}