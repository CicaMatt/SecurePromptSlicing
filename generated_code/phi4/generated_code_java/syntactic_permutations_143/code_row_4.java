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
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null);
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String emailParam = "email=" + query.substring(query.indexOf("=") + 1);
                
                try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
                    String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
                    
                    try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                        pstmt.setString(1, emailParam);
                        
                        try (ResultSet rs = pstmt.executeQuery()) {
                            if (rs.next() && rs.getInt(1) > 0) {
                                sql = "DELETE FROM users WHERE email = ?";
                                
                                try (PreparedStatement deleteStmt = conn.prepareStatement(sql)) {
                                    deleteStmt.setString(1, emailParam);
                                    deleteStmt.executeUpdate();
                                    
                                    String response = "User unsubscribed successfully.";
                                    exchange.sendResponseHeaders(200, response.getBytes().length);
                                    try (OutputStream os = exchange.getResponseBody()) {
                                        os.write(response.getBytes());
                                    }
                                }
                            } else {
                                String response = "The user is not subscribed.";
                                exchange.sendResponseHeaders(404, response.getBytes().length);
                                try (OutputStream os = exchange.getResponseBody()) {
                                    os.write(response.getBytes());
                                }
                            }
                        }
                    }
                } catch (SQLException e) {
                    String response = "Internal server error: " + e.getMessage();
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    try (OutputStream os = exchange.getResponseBody()) {
                        os.write(response.getBytes());
                    }
                }
            } else {
                String response = "Method not allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }
    }
}