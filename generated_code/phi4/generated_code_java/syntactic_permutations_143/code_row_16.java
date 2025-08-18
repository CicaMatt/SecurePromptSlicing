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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) throws IOException {
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
                if (query != null && !query.isEmpty()) {
                    String[] params = query.split("=");
                    if (params.length == 2 && "email".equals(params[0])) {
                        email = params[1];
                    }
                }

                if (email == null || email.isEmpty()) {
                    String response = "Invalid request";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                } else {
                    try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                        if (isSubscribed(conn, email)) {
                            unsubscribeUser(conn, email);
                            String response = "Unsubscribed successfully";
                            exchange.sendResponseHeaders(200, response.getBytes().length);
                        } else {
                            String response = "User is not subscribed";
                            exchange.sendResponseHeaders(404, response.getBytes().length);
                        }
                        OutputStream os = exchange.getResponseBody();
                        os.write(exchange.getResponseHeaders().getFirstValue("Content-Length").getBytes());
                        os.close();
                    } catch (SQLException e) {
                        String response = "Internal server error";
                        exchange.sendResponseHeaders(500, response.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    }
                }
            } else {
                String response = "Method not allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private boolean isSubscribed(Connection conn, String email) throws SQLException {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
            return false;
        }

        private void unsubscribeUser(Connection conn, String email) throws SQLException {
            String query = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }
        }
    }
}


**Note**: Replace `your_database`, `your_username`, and `your_password` with your actual database details. Additionally, ensure you have the MySQL JDBC driver in your classpath for this code to run successfully.