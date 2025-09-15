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
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) throws Exception {
        int serverPort = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(serverPort), 0);
        
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); 
        server.start();
        System.out.println("Server started on port " + serverPort);
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String emailParam = query.split("=")[1];
                
                try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                    if (isUserInDatabase(conn, emailParam)) {
                        deleteUserFromDatabase(conn, emailParam);
                        sendResponse(exchange, "Unsubscribed successfully.");
                    } else {
                        sendResponse(exchange, "User is not subscribed.");
                    }
                } catch (SQLException e) {
                    e.printStackTrace();
                    sendResponse(exchange, "Internal server error.", 500);
                }
            } else {
                sendResponse(exchange, "Method Not Allowed", 405);
            }
        }

        private boolean isUserInDatabase(Connection conn, String email) throws SQLException {
            String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
            return false;
        }

        private void deleteUserFromDatabase(Connection conn, String email) throws SQLException {
            String sql = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
