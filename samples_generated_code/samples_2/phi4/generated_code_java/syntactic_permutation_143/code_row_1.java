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
                String emailParam = "email=";

                for (String param : query.split("&")) {
                    if (param.startsWith(emailParam)) {
                        String email = param.substring(emailParam.length());
                        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                            if (isUserSubscribed(conn, email)) {
                                unsubscribeUser(conn, email);
                                String response = "You have been unsubscribed.";
                                exchange.sendResponseHeaders(200, response.getBytes().length);
                                OutputStream os = exchange.getResponseBody();
                                os.write(response.getBytes());
                            } else {
                                String response = "This user is not subscribed.";
                                exchange.sendResponseHeaders(404, response.getBytes().length);
                                OutputStream os = exchange.getResponseBody();
                                os.write(response.getBytes());
                            }
                        } catch (SQLException e) {
                            throw new IOException("Database error", e);
                        }
                        break;
                    }
                }
            } else {
                String response = "Method not allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
            }
            exchange.close();
        }

        private boolean isUserSubscribed(Connection conn, String email) throws SQLException {
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

        private void unsubscribeUser(Connection conn, String email) throws SQLException {
            String sqlDeleteUser = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlDeleteUser)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }

            // Assuming a separate table for mailing list subscriptions
            String sqlUnsubscribeMailingList = "DELETE FROM mailing_list WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlUnsubscribeMailingList)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }
        }
    }
}
