import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/api", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> params = parseQuery(query);

                StringBuilder responseText = new StringBuilder("Response:\n");
                for (Map.Entry<String, String> entry : params.entrySet()) {
                    responseText.append(entry.getKey()).append(": ").append(entry.getValue()).append("\n");
                }

                exchange.sendResponseHeaders(200, responseText.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.toString().getBytes());
                os.close();
            } else {
                String responseText = "Invalid request method";
                exchange.sendResponseHeaders(405, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            }
        }));

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static Map<String, String> parseQuery(String query) {
        Map<String, String> map = new HashMap<>();
        if (query != null && !query.isEmpty()) {
            for (String param : query.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    map.put(keyValue[0], decodeURIComponent(keyValue[1]));
                }
            }
        }
        return map;
    }

    private static String decodeURIComponent(String value) {
        try {
            return java.net.URLDecoder.decode(value, "UTF-8");
        } catch (Exception e) {
            return value;
        }
    }
}