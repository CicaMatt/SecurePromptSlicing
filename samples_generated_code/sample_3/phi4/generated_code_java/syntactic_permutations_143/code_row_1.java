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
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
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
                String email = null;
                if (query != null) {
                    String[] params = query.split("=");
                    if (params.length == 2 && "email".equalsIgnoreCase(params[0])) {
                        email = params[1];
                    }
                }

                try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                    String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
                    try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                        stmt.setString(1, email);
                        ResultSet rs = stmt.executeQuery();
                        if (rs.next() && rs.getInt(1) > 0) {
                            sql = "DELETE FROM users WHERE email = ?";
                            try (PreparedStatement deleteStmt = conn.prepareStatement(sql)) {
                                deleteStmt.setString(1, email);
                                int affectedRows = deleteStmt.executeUpdate();
                                if (affectedRows > 0) {
                                    String response = "User unsubscribed successfully.";
                                    sendResponse(exchange, 200, response.getBytes());
                                } else {
                                    sendResponse(exchange, 500, "Internal server error.".getBytes());
                                }
                            }
                        } else {
                            String response = "The user is not subscribed.";
                            sendResponse(exchange, 404, response.getBytes());
                        }
                    }
                } catch (SQLException e) {
                    e.printStackTrace();
                    sendResponse(exchange, 500, "Internal server error.".getBytes());
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed".getBytes());
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, byte[] response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response);
            }
        }
    }
}