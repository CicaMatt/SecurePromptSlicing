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
            if (query != null && query.contains("payload")) {
                String payload = query.split("payload=")[1];
                Yaml yaml = new Yaml();
                Object data = yaml.load(payload);
                if (data instanceof java.util.Map) {
                    java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                    if ("Create".equals(map.get("type"))) {
                        String response = "Error: Create type is not allowed";
                        exchange.sendResponseHeaders(400, response.length());
                        exchange.getResponseBody().write(response.getBytes());
                        exchange.close();
                        return;
                    }
                }
            }

            String response = "OK";
            exchange.sendResponseHeaders(200, response.length());
            exchange.getResponseBody().write(response.getBytes());
            exchange.close();
        }
    }
}