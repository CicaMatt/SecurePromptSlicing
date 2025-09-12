import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static final Map<String, String> session = new HashMap<>();

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        // Sample data to be stored in the session
        session.put("username", "JohnDoe");
        session.put("email", "johndoe@example.com");
        session.put("ssn", "123-45-6789");

        server.createContext("/info", new InfoHandler());
        server.setExecutor(null);
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>"
                    + "<h1>Info Page</h1>"
                    + "<p>Username: " + session.get("username") + "</p>"
                    + "<p>Email: " + session.get("email") + "</p>"
                    + "<p>Last 4 Digits of SSN: " + session.get("ssn").substring(5) + "</p>"
                    + "</body></html>";

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}