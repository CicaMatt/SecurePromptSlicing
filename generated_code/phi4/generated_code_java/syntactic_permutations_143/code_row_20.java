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
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class UnsubscribeService {

    private static Connection connectDatabase() throws Exception {
        String url = "jdbc:sqlite:path_to_your_database.db"; // Update the path to your database
        return DriverManager.getConnection(url);
    }

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> queryParams = new HashMap<>();
            if (query != null) {
                StringTokenizer tokenizer = new StringTokenizer(query, "&");
                while (tokenizer.hasMoreTokens()) {
                    String param = tokenizer.nextToken();
                    int idx = param.indexOf("=");
                    queryParams.put(param.substring(0, idx), param.substring(idx + 1));
                }
            }

            String email = queryParams.get("email");
            if (email == null || email.isEmpty()) {
                sendResponse(exchange, 400, "Bad Request: Email parameter is required.");
                return;
            }

            try (Connection conn = connectDatabase()) {
                if (isUserSubscribed(conn, email)) {
                    unsubscribeUser(conn, email);
                    sendResponse(exchange, 200, "You have been successfully unsubscribed.");
                } else {
                    sendResponse(exchange, 404, "The user is not subscribed.");
                }
            } catch (Exception e) {
                sendResponse(exchange, 500, "Internal Server Error: " + e.getMessage());
            }
        }

        private boolean isUserSubscribed(Connection conn, String email) throws Exception {
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

        private void unsubscribeUser(Connection conn, String email) throws Exception {
            String deleteQuery = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(deleteQuery)) {
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


**Note:** Replace `path_to_your_database.db` with the actual path to your SQLite database. Ensure that you have the necessary JDBC driver for SQLite in your classpath. This example uses an embedded HTTP server from Java's standard library and SQLite for simplicity, but you might need to adapt it for a production environment with more robust solutions like Spring Boot or similar frameworks for web services, along with a more scalable database system.