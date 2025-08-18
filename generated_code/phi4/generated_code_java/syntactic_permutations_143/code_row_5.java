import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class UnsubscribeService {

    private static Connection getConnection() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password"
        );
    }

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equalsIgnoreCase(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String emailParam = "email=";

                if (query != null && query.startsWith(emailParam)) {
                    String email = query.substring(emailParam.length());

                    try (Connection connection = getConnection()) {
                        PreparedStatement checkStmt = connection.prepareStatement("SELECT * FROM users WHERE email = ?");
                        checkStmt.setString(1, email);
                        ResultSet resultSet = checkStmt.executeQuery();

                        if (resultSet.next()) {
                            PreparedStatement deleteStmt = connection.prepareStatement(
                                    "DELETE FROM users WHERE email = ?"
                            );
                            deleteStmt.setString(1, email);
                            int affectedRows = deleteStmt.executeUpdate();

                            if (affectedRows > 0) {
                                String response = "User unsubscribed successfully.";
                                exchange.sendResponseHeaders(200, response.getBytes().length);
                                OutputStream os = exchange.getResponseBody();
                                os.write(response.getBytes());
                            } else {
                                String response = "Failed to unsubscribe user.";
                                exchange.sendResponseHeaders(500, response.getBytes().length);
                                OutputStream os = exchange.getResponseBody();
                                os.write(response.getBytes());
                            }
                        } else {
                            String response = "User is not subscribed.";
                            exchange.sendResponseHeaders(404, response.getBytes().length);
                            OutputStream os = exchange.getResponseBody();
                            os.write(response.getBytes());
                        }
                    } catch (SQLException | ClassNotFoundException e) {
                        String response = "Internal server error: " + e.getMessage();
                        exchange.sendResponseHeaders(500, response.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                    }
                } else {
                    String response = "Invalid request. Please provide an email parameter.";
                    exchange.sendResponseHeaders(400, response.getBytes().lightlength());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                }

                exchange.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                exchange.close();
            }
        }
    }
}


**Note:** Replace `"jdbc:mysql://localhost:3306/your_database"`, `"username"`, and `"password"` with your actual database connection details. Also, ensure that you have the MySQL JDBC driver in your classpath or dependencies to run this code successfully.