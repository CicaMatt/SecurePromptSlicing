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
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null);
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            String emailParam = null;

            if (query != null && !query.isEmpty()) {
                String[] params = query.split("&");
                for (String param : params) {
                    String[] keyValue = param.split("=");
                    if ("email".equals(keyValue[0])) {
                        emailParam = keyValue[1];
                        break;
                    }
                }
            }

            if (emailParam == null || emailParam.isEmpty()) {
                sendResponse(exchange, 400, "Email parameter is missing");
                return;
            }

            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setString(1, emailParam);
                    ResultSet rs = stmt.executeQuery();

                    if (rs.next() && rs.getInt(1) > 0) {
                        deleteEmailFromDatabase(conn, emailParam);
                        sendResponse(exchange, 200, "Successfully unsubscribed");
                    } else {
                        sendResponse(exchange, 404, "Email not found in database");
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
                sendResponse(exchange, 500, "Internal server error");
            }
        }

        private void deleteEmailFromDatabase(Connection conn, String email) throws SQLException {
            String sqlDelete = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlDelete)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}