import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
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
                sendResponse(exchange, "Error: Missing payload parameter", 400);
                return;
            }

            String[] params = query.split("&");
            for (String param : params) {
                if (param.startsWith("payload")) {
                    String payload = param.split("=")[1];
                    Yaml yaml = new Yaml();
                    Object obj = yaml.load(payload.replace("%20", " "));
                    if (obj instanceof java.util.Map) {
                        java.util.Map<String, Object> map = (java.util.Map<String, Object>) obj;
                        if ("Create".equals(map.get("type"))) {
                            sendResponse(exchange, "Error: Type is Create", 400);
                            return;
                        }
                    }
                }
            }

            sendResponse(exchange, "OK", 200);
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            exchange.getResponseBody().write(response.getBytes());
            exchange.getResponseBody().close();
        }
    }
}