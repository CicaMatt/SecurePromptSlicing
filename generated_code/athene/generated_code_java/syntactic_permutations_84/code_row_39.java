import java.io.IOException;
import java.net.http.HttpHandler;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.http.HttpServer;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandlers;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/webhook", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            String query = t.getRequestURI().getQuery();
            if (query == null || !query.contains("payload")) {
                sendResponse(t, "400", "");
                return;
            }

            String payload = query.split("=")[1];
            ObjectMapper yamlReader = new ObjectMapper(new YAMLFactory());
            try {
                PayloadData data = yamlReader.readValue(payload, PayloadData.class);
                if ("Create".equals(data.getType())) {
                    sendResponse(t, "200", "OK");
                } else {
                    sendResponse(t, "400", "Invalid type");
                }
            } catch (Exception e) {
                sendResponse(t, "400", "Invalid payload");
            }
        }

        private void sendResponse(HttpExchange t, String codeStr, String response) throws IOException {
            int code = Integer.parseInt(codeStr);
            t.sendResponseHeaders(code, response.length());
            t.getResponseOutputStream().write(response.getBytes());
            t.close();
        }
    }

    static class PayloadData {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}