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
        server.setExecutor(null);
        server.start();
        System.out.println("Server started on port " + port);
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String email = null;
                
                if (query != null && query.startsWith("email=")) {
                    email = query.substring(6);
                }

                if (email == null || email.isEmpty()) {
                    sendResponse(exchange, 400, "Invalid request. Please provide an email parameter.");
                    return;
                }

                try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                    String sql = "SELECT COUNT(*) FROM mailing_list WHERE email = ?";
                    
                    try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                        stmt.setString(1, email);
                        
                        try (ResultSet rs = stmt.executeQuery()) {
                            if (rs.next() && rs.getInt(1) > 0) {
                                sql = "DELETE FROM mailing_list WHERE email = ?";
                                
                                try (PreparedStatement deleteStmt = conn.prepareStatement(sql)) {
                                    deleteStmt.setString(1, email);
                                    deleteStmt.executeUpdate();
                                    
                                    sendResponse(exchange, 200, "Unsubscribed successfully.");
                                }
                            } else {
                                sendResponse(exchange, 404, "Email not subscribed.");
                            }
                        }
                    }
                } catch (SQLException e) {
                    e.printStackTrace();
                    sendResponse(exchange, 500, "Internal server error.");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed. Only GET is supported.");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}


**Note**: Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Additionally, ensure the JDBC driver for MySQL is included in your classpath.