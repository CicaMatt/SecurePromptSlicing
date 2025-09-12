import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/webhook", new WebHookHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class WebHookHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query == null || !query.contains("payload")) {
                sendResponse(exchange, "Error: payload parameter is missing", 400);
                return;
            }

            String[] params = query.split("&");
            String payloadValue = "";
            for (String param : params) {
                if (param.startsWith("payload=")) {
                    payloadValue = param.substring("payload=".length());
                    break;
                }
            }

            try {
                Yaml yaml = new Yaml();
                InputStream inputStream = new ByteArrayInputStream(payloadValue.getBytes());
                Object data = yaml.load(inputStream);
                if (!(data instanceof java.util.Map)) {
                    sendResponse(exchange, "Error: Invalid payload format", 400);
                    return;
                }
                java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                String type = (String) map.get("type");
                if ("Create".equals(type)) {
                    sendResponse(exchange, "Error: Create type is not allowed", 400);
                } else {
                    sendResponse(exchange, "Success", 200);
                }
            } catch (Exception e) {
                sendResponse(exchange, "Error: Invalid YAML payload", 400);
            }
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            byte[] responseBytes = response.getBytes();
            exchange.sendResponseHeaders(statusCode, responseBytes.length);
            OutputStream os = exchange.getResponseBody();
            os.write(responseBytes);
            os.close();
        }
    }
}