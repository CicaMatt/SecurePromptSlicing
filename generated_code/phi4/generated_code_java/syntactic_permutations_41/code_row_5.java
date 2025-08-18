import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UserInfoApp {

    private static final String USERNAME = "JohnDoe";
    private static final String EMAIL = "johndoe@example.com";
    private static final String SSN_LAST_FOUR_DIGITS = "1234";

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server is listening on port " + port);
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + USERNAME + "</p>"
                    + "<p>Email: " + EMAIL + "</p>"
                    + "<p>Last 4 digits of SSN: " + SSN_LAST_FOUR_DIGITS + "</p>"
                    + "</body></html>";

            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}