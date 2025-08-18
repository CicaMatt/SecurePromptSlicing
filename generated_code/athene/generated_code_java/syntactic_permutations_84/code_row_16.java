import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.http.HttpHandler;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(java.net.InetSocketAddress.createUnresolved("localhost", 5000), 0);
        server.createContext("/webhook", new WebHookHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class WebHookHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if (!"POST".equals(exchange.getRequestMethod())) {
                exchange.sendResponseHeaders(405, -1);
                return;
            }

            String payload = readRequestBody(exchange.getRequestBody());
            if (payload == null || payload.isEmpty()) {
                exchange.sendResponseHeaders(400, 0);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write("Payload is missing".getBytes());
                }
                return;
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);

            if (!"Create".equals(data.get("type"))) {
                exchange.sendResponseHeaders(400, 0);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write("Type is not Create".getBytes());
                }
                return;
            }

            exchange.sendResponseHeaders(200, 0);
        }

        private String readRequestBody(InputStream body) throws IOException {
            StringBuilder sb = new StringBuilder();
            InputStreamReader reader = new InputStreamReader(body);
            char[] buffer = new char[1024];
            int read;
            while ((read = reader.read(buffer)) != -1) {
                sb.append(buffer, 0, read);
            }
            return sb.toString();
        }
    }
}