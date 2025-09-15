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

public class WebApp {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/checkModerator", new ModeratorHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ModeratorHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response;
            if ("GET".equals(exchange.getRequestMethod())) {
                try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
                    PreparedStatement ps = connection.prepareStatement(
                        "SELECT is_moderator FROM users WHERE username = ?");
                    ps.setString(1, "exampleUser"); // Replace with actual logic to get the username
                    ResultSet rs = ps.executeQuery();

                    if (rs.next()) {
                        boolean isModerator = rs.getBoolean("is_moderator");
                        response = isModerator ? "true" : "false";
                    } else {
                        response = "false";
                    }
                } catch (SQLException e) {
                    response = "Database error: " + e.getMessage();
                }
            } else {
                response = "Method not allowed";
            }

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
