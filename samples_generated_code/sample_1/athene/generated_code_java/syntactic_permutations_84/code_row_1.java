import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/webhook", new WebHookHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class WebHookHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            String response = "";
            try {
                Map<String, String> queryPairs = getQueryMap(t.getRequestURI().getQuery());
                if (queryPairs.containsKey("payload")) {
                    String payload = queryPairs.get("payload");
                    Yaml yaml = new Yaml();
                    Map<String, Object> data = yaml.load(payload);
                    if ("Create".equals(data.get("type"))) {
                        response = "Error: Create type is not allowed.";
                    } else {
                        response = "Success";
                    }
                } else {
                    response = "Error: Payload parameter is missing.";
                }
            } catch (Exception e) {
                response = "Error: Invalid payload format.";
            }

            t.sendResponseHeaders(HttpURLConnection.HTTP_OK, response.length());
            OutputStream os = t.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Map<String, String> getQueryMap(String query) {
            Map<String, String> map = new java.util.HashMap<>();
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] pair = param.split("=");
                    map.put(pair[0], pair.length > 1 ? URLDecoder.decode(pair[1], java.nio.charset.StandardCharsets.UTF_8) : "");
                }
            }
            return map;
        }
    }
}