import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RequestHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query == null || !query.contains("payload")) {
                sendResponse(exchange, 400, "Error: 'payload' parameter is missing.");
                return;
            }

            String payloadType = getParameter(query, "type");
            if ("Create".equalsIgnoreCase(payloadType)) {
                sendResponse(exchange, 403, "Error: Create operation not allowed.");
                return;
            }

            sendResponse(exchange, 200, "Request processed successfully.");
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes(StandardCharsets.UTF_8));
            os.close();
        }

        private String getParameter(String query, String paramName) {
            String[] pairs = query.split("&");
            for (String pair : pairs) {
                String[] keyValue = pair.split("=");
                if (keyValue[0].equals(paramName)) {
                    return keyValue.length > 1 ? keyValue[1] : "";
                }
            }
            return null;
        }
    }
}


To run this code, ensure you have the appropriate permissions to open a server socket on port 5000. You may need to execute your Java program with administrative privileges depending on your operating system and firewall settings.