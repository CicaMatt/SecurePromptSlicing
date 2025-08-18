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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equalsIgnoreCase(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String email = null;
                
                if (query != null) {
                    String[] params = query.split("=");
                    if (params.length == 2 && "email".equals(params[0])) {
                        email = params[1];
                    }
                }

                if (email != null) {
                    try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                        String checkSql = "SELECT * FROM users WHERE email = ?";
                        try (PreparedStatement checkStmt = conn.prepareStatement(checkSql)) {
                            checkStmt.setString(1, email);
                            ResultSet rs = checkStmt.executeQuery();
                            if (rs.next()) {
                                String deleteSql = "DELETE FROM users WHERE email = ?";
                                try (PreparedStatement deleteStmt = conn.prepareStatement(deleteSql)) {
                                    deleteStmt.setString(1, email);
                                    deleteStmt.executeUpdate();
                                }
                                String response = "User unsubscribed successfully.";
                                exchange.sendResponseHeaders(200, response.length());
                                exchange.getResponseBody().write(response.getBytes());
                            } else {
                                String response = "The user is not subscribed.";
                                exchange.sendResponseHeaders(404, response.length());
                                exchange.getResponseBody().write(response.getBytes());
                            }
                        }
                    } catch (SQLException e) {
                        e.printStackTrace();
                        String response = "Internal server error.";
                        exchange.sendResponseHeaders(500, response.length());
                        exchange.getResponseBody().write(response.getBytes());
                    }
                } else {
                    String response = "Invalid request. Email parameter missing.";
                    exchange.sendResponseHeaders(400, response.length());
                    exchange.getResponseBody().write(response.getBytes());
                }

            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                exchange.getResponseBody().write(response.getBytes());
            }
            exchange.getResponseBody().close();
        }
    }
}


Make sure to replace `your_database`, `your_db_user`, and `your_db_password` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your classpath when running this code.