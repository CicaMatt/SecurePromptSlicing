import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetSocketAddress;
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
        public void handle(HttpExchange t) throws IOException {
            String response = "";
            try {
                String query = t.getRequestURI().getQuery();
                if (query == null || !query.contains("payload")) {
                    response = "Error: payload parameter is missing";
                } else {
                    String payload = query.split("payload=")[1];
                    Yaml yaml = new Yaml();
                    Object data = yaml.load(payload);
                    if (data instanceof java.util.Map) {
                        java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                        if ("Create".equals(map.get("type"))) {
                            response = "Error: type is Create";
                        } else {
                            response = "Success: Payload received and processed";
                        }
                    } else {
                        response = "Error: Invalid payload format";
                    }
                }
            } catch (Exception e) {
                response = "Error: " + e.getMessage();
            }

            t.sendResponseHeaders(200, response.length());
            OutputStream os = t.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}