import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                if (query != null && query.startsWith("email=")) {
                    String email = query.substring(6);
                    try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                        PreparedStatement stmt = conn.prepareStatement("SELECT COUNT(*) FROM users WHERE email = ?");
                        stmt.setString(1, email);
                        ResultSet rs = stmt.executeQuery();
                        
                        if (rs.next() && rs.getInt(1) > 0) {
                            stmt = conn.prepareStatement("DELETE FROM users WHERE email = ?");
                            stmt.setString(1, email);
                            stmt.executeUpdate();

                            // Assuming a method unsubscribeFromMailingList exists
                            unsubscribeFromMailingList(email);

                            String response = "User unsubscribed successfully.";
                            sendResponse(exchange, 200, response);
                        } else {
                            String response = "User is not subscribed.";
                            sendResponse(exchange, 404, response);
                        }
                    } catch (SQLException e) {
                        e.printStackTrace();
                        sendResponse(exchange, 500, "Internal server error.");
                    }
                } else {
                    sendResponse(exchange, 400, "Invalid request. Please specify an email parameter.");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private void unsubscribeFromMailingList(String email) {
            // Implement your mailing list unsubscription logic here
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


Make sure to replace `your_database`, `root`, and `password` with your actual database name, username, and password. Also, implement the `unsubscribeFromMailingList` method as needed for your mailing list logic.