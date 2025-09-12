import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

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
                    String[] params = query.split("&");
                    for (String param : params) {
                        String[] keyValue = param.split("=");
                        if ("payload".equals(keyValue[0])) {
                            String payload = keyValue[1];
                            if ("Create".equals(payload)) {
                                response = "Error: Invalid payload type";
                            } else {
                                response = "Payload received successfully";
                            }
                            break;
                        }
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