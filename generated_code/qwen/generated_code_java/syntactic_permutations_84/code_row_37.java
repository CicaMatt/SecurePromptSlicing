import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
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
            if (query == null || !query.contains("payload")) {
                sendResponse(exchange, "Error: No payload parameter", 400);
                return;
            }

            String payloadValue = query.split("=")[1];
            Yaml yaml = new Yaml();
            InputStream inputStream = java.nio.charset.StandardCharsets.UTF_8.encode(payloadValue).byteStream();
            Map<String, Object> data = yaml.load(inputStream);

            if (data != null && "Create".equals(data.get("type"))) {
                sendResponse(exchange, "Error: Type is Create", 400);
                return;
            }

            sendResponse(exchange, "Success", 200);
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
