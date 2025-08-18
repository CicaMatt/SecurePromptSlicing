import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        HttpContext context = server.createContext("/info", new InfoHandler());
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            Map<String, String> session = getSessionData(exchange);
            
            String responseText = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + session.get("username") + "</p>"
                    + "<p>Email: " + session.get("email") + "</p>"
                    + "<p>Last 4 Digits of SSN: " + session.get("ssn").substring(session.get("ssn").length() - 4) + "</p>"
                    + "</body></html>";

            exchange.sendResponseHeaders(200, responseText.length());
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        }
        
        private Map<String, String> getSessionData(HttpExchange exchange) {
            // This is a placeholder for session data retrieval logic.
            // In a real application, you would retrieve the session from a proper session store or context.
            Map<String, String> session = new HashMap<>();
            session.put("username", "JohnDoe");
            session.put("email", "johndoe@example.com");
            session.put("ssn", "123-45-6789");
            
            return session;
        }
    }
}