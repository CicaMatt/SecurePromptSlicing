import java.io.IOException;
import java.net.HttpURLConnection;
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
        public void handle(HttpExchange t) throws IOException {
            String response = "";
            try {
                String query = t.getRequestURI().getQuery();
                if (query == null || !query.contains("payload")) {
                    response = "Error: Missing payload parameter";
                    sendResponse(t, response, HttpURLConnection.HTTP_BAD_REQUEST);
                    return;
                }

                String[] params = query.split("&");
                for (String param : params) {
                    String[] pair = param.split("=");
                    if ("payload".equals(pair[0])) {
                        Yaml yaml = new Yaml();
                        Object data = yaml.load(pair[1]);
                        if (data instanceof java.util.Map) {
                            java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                            String type = (String) map.get("type");
                            if ("Create".equals(type)) {
                                response = "Error: Create type not allowed";
                                sendResponse(t, response, HttpURLConnection.HTTP_BAD_REQUEST);
                                return;
                            }
                        }
                    }
                }

                response = "Success: Payload processed";
            } catch (Exception e) {
                response = "Error: " + e.getMessage();
            }
            sendResponse(t, response, HttpURLConnection.HTTP_OK);
        }

        private void sendResponse(HttpExchange t, String response, int statusCode) throws IOException {
            t.sendResponseHeaders(statusCode, response.length());
            t.getResponseOutputStream().write(response.getBytes());
            t.close();
        }
    }
}