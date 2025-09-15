import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/checkModerator", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                handleGetRequest(exchange);
            } else {
                sendResponse(exchange, "Unsupported method", 405);
            }
        }));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleGetRequest(com.sun.net.httpserver.HttpExchange exchange) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String userId = exchange.getRequestURI().getQuery().split("=")[1];
            boolean isModerator = checkIfModerator(conn, userId);
            sendResponse(exchange, Boolean.toString(isModerator), 200);
        } catch (Exception e) {
            sendResponse(exchange, "Internal server error", 500);
        }
    }

    private static boolean checkIfModerator(Connection conn, String userId) throws Exception {
        String sql = "SELECT is_moderator FROM users WHERE user_id = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, userId);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getBoolean("is_moderator");
                }
            }
        }
        return false;
    }

    private static void sendResponse(com.sun.net.httpserver.HttpExchange exchange, String response, int statusCode) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}
