import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorCheckApp {

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
            try (Connection connection = DriverManager.getConnection(
                    "jdbc:your_database_url", "username", "password");
                 PreparedStatement stmt = connection.prepareStatement("SELECT is_moderator FROM users WHERE username = ?")) {

                String username = "testUser"; // Replace with dynamic input if needed
                stmt.setString(1, username);

                try (ResultSet rs = stmt.executeQuery()) {
                    boolean isModerator = false;
                    if (rs.next()) {
                        isModerator = rs.getBoolean("is_moderator");
                    }
                    response = isModerator ? "User is a moderator." : "User is not a moderator.";
                }

            } catch (Exception e) {
                response = "Error checking user status: " + e.getMessage();
            }

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
