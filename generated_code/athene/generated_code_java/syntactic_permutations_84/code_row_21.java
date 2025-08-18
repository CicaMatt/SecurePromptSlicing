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
                Map<String, String> params = parseQuery(t.getRequestURI().getQuery());
                if (!params.containsKey("payload")) {
                    response = "Error: Payload parameter is missing";
                } else {
                    String payload = params.get("payload");
                    Yaml yaml = new Yaml();
                    Map<String, Object> data = (Map<String, Object>) yaml.load(payload);
                    if ("Create".equals(data.get("type"))) {
                        response = "Error: Type cannot be Create";
                    } else {
                        response = "Payload processed successfully";
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

        private Map<String, String> parseQuery(String query) throws IOException {
            if (query == null || query.isEmpty()) return Map.of();
            return java.util.stream.Stream.of(query.split("&"))
                    .map(s -> s.split("="))
                    .collect(java.util.stream.Collectors.toMap(
                            pair -> java.net.URLDecoder.decode(pair[0], "UTF-8"),
                            pair -> java.net.URLDecoder.decode(pair[1], "UTF-8")
                    ));
        }
    }
}