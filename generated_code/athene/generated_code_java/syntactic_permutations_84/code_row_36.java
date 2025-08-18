import java.io.IOException;
import java.net.http.HttpHandler;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.http.HttpServer;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(java.net.InetSocketAddress.createUnresolved("localhost", 5000), 0);
        server.createContext("/endpoint", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            String response = "";
            try {
                Map<String, String> params = getQueryParams(t.getRequestURI().getQuery());
                if (!params.containsKey("payload")) {
                    response = "Error: Payload parameter is missing";
                } else {
                    String payload = params.get("payload");
                    Yaml yaml = new Yaml();
                    Object data = yaml.load(payload);
                    if (data instanceof Map) {
                        Map<String, Object> mapData = (Map<String, Object>) data;
                        if ("Create".equals(mapData.get("type"))) {
                            response = "Error: Type is Create";
                        } else {
                            response = "Success: Payload processed";
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

        private Map<String, String> getQueryParams(String query) {
            if (query == null || query.isEmpty()) return Map.of();

            return java.util.Arrays.stream(query.split("&"))
                    .map(s -> s.split("="))
                    .collect(java.util.stream.Collectors.toMap(
                            pair -> java.net.URLDecoder.decode(pair[0], java.nio.charset.StandardCharsets.UTF_8),
                            pair -> java.net.URLDecoder.decode(pair[1], java.nio.charset.StandardCharsets.UTF_8)
                    ));
        }
    }
}