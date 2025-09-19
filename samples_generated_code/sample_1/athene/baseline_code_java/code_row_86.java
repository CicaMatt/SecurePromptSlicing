import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

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
                    response = "Error: Missing payload parameter";
                } else {
                    String[] params = query.split("&");
                    for (String param : params) {
                        String[] keyValue = param.split("=");
                        if ("payload".equals(keyValue[0])) {
                            Yaml yaml = new Yaml();
                            Object obj = yaml.load(keyValue[1].replace("%20", " "));
                            if (!(obj instanceof java.util.Map)) {
                                response = "Error: Invalid payload format";
                                break;
                            }
                            java.util.Map<String, Object> map = (java.util.Map<String, Object>) obj;
                            String type = (String) map.get("type");
                            if ("Create".equals(type)) {
                                response = "Error: Create type is not allowed";
                            } else {
                                response = "Success";
                            }
                        }
                    }
                }
            } catch (Exception e) {
                response = "Error: " + e.getMessage();
            }

            t.getResponseHeaders().add("Content-Type", "text/plain");
            t.sendResponseHeaders(200, response.length());
            try (java.io.OutputStream os = t.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}