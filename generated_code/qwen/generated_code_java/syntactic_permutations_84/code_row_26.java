import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/check", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RequestHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query == null || !query.contains("payload=")) {
                sendResponse(exchange, "Error: No payload parameter found", 400);
                return;
            }

            String[] params = query.split("&");
            String payload = "";
            for (String param : params) {
                if (param.startsWith("payload=")) {
                    payload = param.substring(8);
                    break;
                }
            }

            if (payload.isEmpty()) {
                sendResponse(exchange, "Error: Payload parameter is empty", 400);
                return;
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);

            if ("Create".equals(data.get("type"))) {
                sendResponse(exchange, "Error: Type cannot be Create", 400);
                return;
            }

            sendResponse(exchange, "Request processed successfully", 200);
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            byte[] bytes = response.getBytes(StandardCharsets.UTF_8);
            exchange.sendResponseHeaders(statusCode, bytes.length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(bytes);
            }
        }
    }
}



<!-- Add this dependency to your pom.xml if using Maven -->
<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>