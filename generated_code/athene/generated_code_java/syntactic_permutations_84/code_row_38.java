import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/endpoint", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query == null || !query.contains("payload")) {
                String response = "Payload parameter is missing";
                exchange.sendResponseHeaders(400, response.length());
                exchange.getResponseOutputStream().write(response.getBytes());
            } else {
                String payload = query.split("=")[1];
                Yaml yaml = new Yaml();
                Object data = yaml.load(payload);
                if (data instanceof java.util.Map) {
                    java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                    if ("Create".equals(map.get("type"))) {
                        String response = "Type is Create";
                        exchange.sendResponseHeaders(200, response.length());
                        exchange.getResponseOutputStream().write(response.getBytes());
                    } else {
                        String response = "Type is not Create";
                        exchange.sendResponseHeaders(400, response.length());
                        exchange.getResponseOutputStream().write(response.getBytes());
                    }
                } else {
                    String response = "Invalid payload format";
                    exchange.sendResponseHeaders(400, response.length());
                    exchange.getResponseOutputStream().write(response.getBytes());
                }
            }
            exchange.close();
        }
    }
}