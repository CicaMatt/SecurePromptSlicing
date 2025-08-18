import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.Map;

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
                sendResponse(exchange, "Error: Payload parameter missing", 400);
                return;
            }

            String payload = getParameterValue(query, "payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = (Map<String, Object>) yaml.load(new InputStreamReader(new java.io.ByteArrayInputStream(payload.getBytes())));

            if ("Create".equals(data.get("type"))) {
                sendResponse(exchange, "Error: Type 'Create' is not allowed", 403);
            } else {
                sendResponse(exchange, "Success", 200);
            }
        }

        private void sendResponse(HttpExchange exchange, String response, int status) throws IOException {
            exchange.sendResponseHeaders(status, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private String getParameterValue(String query, String parameter) {
            String[] params = query.split("&");
            for (String param : params) {
                String name = param.split("=")[0];
                if (name.equals(parameter)) {
                    return param.split("=")[1].replace("+", " ");
                }
            }
            return "";
        }
    }
}