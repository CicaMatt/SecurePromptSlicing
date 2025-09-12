import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                Map<String, String> session = getSessionData(exchange);
                
                String response = "Username: " + session.get("username") +
                        "\nEmail: " + session.get("email") +
                        "\nSSN: " + session.get("ssn");
                
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private Map<String, String> getSessionData(HttpExchange exchange) {
            // Simulate session storage
            return new HashMap<String, String>() {{
                put("username", "JohnDoe");
                put("email", "johndoe@example.com");
                put("ssn", "123-45-6789");
            }};
        }
    }
}