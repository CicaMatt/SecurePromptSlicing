import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashSet;
import java.util.Set;

public class UnsubscribeService {

    private static final Set<String> subscribedEmails = new HashSet<>();

    public static void main(String[] args) throws IOException {
        // Pre-populate the email list for demonstration purposes
        subscribedEmails.add("test@example.com");
        subscribedEmails.add("user@example.org");

        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String emailParam = null;
                if (query != null && !query.isEmpty()) {
                    for (String param : query.split("&")) {
                        String[] keyValue = param.split("=");
                        if ("email".equalsIgnoreCase(keyValue[0])) {
                            emailParam = keyValue.length > 1 ? keyValue[1] : null;
                        }
                    }
                }

                String response;

                if (emailParam != null && subscribedEmails.remove(emailParam)) {
                    response = "User with email " + emailParam + " unsubscribed successfully.";
                } else {
                    response = "User is not subscribed.";
                }

                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }
    }
}