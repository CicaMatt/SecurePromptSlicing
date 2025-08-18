import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

public class WebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/webhook", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            String response = "";
            try {
                String query = t.getRequestURI().getQuery();
                if (query == null || !query.contains("payload")) {
                    response = "Parameter 'payload' is missing";
                } else {
                    String[] params = query.split("&");
                    for (String param : params) {
                        if (param.startsWith("payload=")) {
                            String payload = param.substring(8);
                            Yaml yaml = new Yaml();
                            Object data = yaml.load(payload);
                            if (data instanceof java.util.Map) {
                                java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                                if ("Create".equals(map.get("type"))) {
                                    response = "Error: Type is Create";
                                } else {
                                    response = "Payload received successfully";
                                }
                            } else {
                                response = "Invalid YAML format";
                            }
                        }
                    }
                }
            } catch (Exception e) {
                response = "An error occurred: " + e.getMessage();
            }

            t.sendResponseHeaders(200, response.length());
            try (java.io.OutputStream os = t.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}