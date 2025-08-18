import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/process", new MyHandler());
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
                    String payload = query.split("payload=")[1];
                    if ("Create".equals(payload)) {
                        response = "Error: Payload type is Create";
                    } else {
                        response = "Payload received successfully";
                    }
                }
            } catch (Exception e) {
                response = "Error processing request: " + e.getMessage();
            }

            t.sendResponseHeaders(200, response.length());
            OutputStream os = t.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}