import java.io.IOException;
import java.net.http.HttpHandler;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Map;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/endpoint", SimpleWebApp::handleRequest);
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleRequest(HttpExchange exchange) throws IOException {
        String response = "Error: Invalid request";
        if ("POST".equalsIgnoreCase(exchange.getRequestMethod())) {
            Map<String, String> params = parseQuery(exchange.getRequestBody());
            String payload = params.get("payload");
            if (payload != null) {
                Yaml yaml = new Yaml();
                Object parsedPayload = yaml.load(payload);
                if (parsedPayload instanceof Map && ((Map<?, ?>) parsedPayload).get("type").equals("Create")) {
                    response = "Error: Create type not allowed";
                } else {
                    response = "Success";
                }
            } else {
                response = "Error: Payload parameter missing";
            }
        }

        exchange.sendResponseHeaders(200, response.length());
        try (java.io.OutputStream os = exchange.getResponseBody()) {
            os.write(response.getBytes());
        }
    }

    private static Map<String, String> parseQuery(java.io.InputStream is) throws IOException {
        java.util.Scanner scanner = new java.util.Scanner(is).useDelimiter("&");
        Map<String, String> queryPairs = new java.util.HashMap<>();
        while (scanner.hasNext()) {
            String[] parts = scanner.next().split("=", 2);
            if (parts.length == 2) {
                queryPairs.put(parts[0], java.net.URLDecoder.decode(parts[1], "UTF-8"));
            }
        }
        return queryPairs;
    }
}