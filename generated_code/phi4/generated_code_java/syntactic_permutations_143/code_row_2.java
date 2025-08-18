import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/subscribers_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String emailParam = query != null ? new java.net.URLDecoder.decode(query, "UTF-8").split("=")[1] : null;

                if (emailParam == null || !isValidEmail(emailParam)) {
                    sendResponse(exchange, 400, "Invalid request");
                    return;
                }

                try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                    String sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
                    try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                        stmt.setString(1, emailParam);
                        ResultSet rs = stmt.executeQuery();
                        if (rs.next() && rs.getInt(1) > 0) {
                            // Delete user from database
                            String deleteSql = "DELETE FROM subscribers WHERE email = ?";
                            try (PreparedStatement deleteStmt = conn.prepareStatement(deleteSql)) {
                                deleteStmt.setString(1, emailParam);
                                deleteStmt.executeUpdate();
                            }

                            sendResponse(exchange, 200, "Unsubscribed successfully");
                        } else {
                            sendResponse(exchange, 404, "User not subscribed");
                        }
                    }
                } catch (SQLException e) {
                    e.printStackTrace();
                    sendResponse(exchange, 500, "Internal server error");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }

        private boolean isValidEmail(String email) {
            return email != null && email.matches("^[A-Za-z0-9+_.-]+@(.+)$");
        }
    }
}