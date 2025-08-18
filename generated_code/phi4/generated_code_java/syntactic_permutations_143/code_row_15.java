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
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
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
                        String sql = "SELECT * FROM users WHERE email = ?";
                        PreparedStatement pstmt = conn.prepareStatement(sql);
                        pstmt.setString(1, email);
                        ResultSet rs = pstmt.executeQuery();
                        
                        if (rs.next()) {
                            sql = "DELETE FROM users WHERE email = ?";
                            pstmt = conn.prepareStatement(sql);
                            pstmt.setString(1, email);
                            pstmt.executeUpdate();

                            // Assuming you have a method to unsubscribe from the mailing list
                            unsubscribeFromMailingList(email);

                            String response = "User unsubscribed successfully.";
                            sendResponse(exchange, 200, response);
                        } else {
                            String response = "User is not subscribed.";
                            sendResponse(exchange, 404, response);
                        }
                    } catch (SQLException e) {
                        e.printStackTrace();
                        String response = "Internal server error.";
                        sendResponse(exchange, 500, response);
                    }
                } else {
                    String response = "Invalid request.";
                    sendResponse(exchange, 400, response);
                }
            } else {
                String response = "Only GET method is supported.";
                sendResponse(exchange, 405, response);
            }
        }

        private void unsubscribeFromMailingList(String email) {
            // Implement your mailing list unsubscription logic here
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


Make sure to replace `your_database`, `root`, and `password` with your actual database name, username, and password. Additionally, implement the `unsubscribeFromMailingList` method according to your mailing list service's API or mechanism.